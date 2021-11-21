//
// Created by Yauheni Sharamed on 20.11.2021.
//

#include "CircuitActive.h"

double CircuitActive::FindCurrent(int i1, int i2) {
    FindMaxTree();
    FindMeshCurrents();
    FindCurrentsFromMesh();

    for(auto & wire : _wires){
        if(wire.GetIndex1() == i1 && wire.GetIndex2() == i2)
            return wire.GetI();
        else if(wire.GetIndex1() == i2 && wire.GetIndex2() == i1)
            return -1.0*wire.GetI();
    }
    std::cout << "Invalid requested current" << std::endl;
    return 0;
}

void CircuitActive::FindMaxTree() {
    for(auto & wire : _wires){
        wire.SetExcluded(true);
        if(IsMonoTree())
            _wremoved.emplace_back(&wire);
        else
            wire.SetExcluded(false);
    }
}

void CircuitActive::CalcMatrix(Matrix& C, Matrix& Z, Matrix& E) {
    for(size_t i = 0; i < E.GetXDem(); ++i){
        E[0][i] = _wires[i].GetE();
        Z[i][i] = _wires[i].GetR();
    }

    for(size_t i = 0; i < C.GetXDem(); ++i){
        _wremoved[i]->SetExcluded(false);
        auto path = FindNoMonoTreePath(*_wremoved[i]);
        _no_mono_paths.emplace_back(std::make_pair(path, 0));
        for(size_t j = 0; j < C.GetYDem(); ++j){
            for(size_t k = 0; k < path.size()-1; ++k){
                if(path[k] == _wires[j].GetIndex1() && path[k+1] == _wires[j].GetIndex2())
                    C[j][i] = 1;
                else if (path[k] == _wires[j].GetIndex2() && path[k+1] == _wires[j].GetIndex1())
                    C[j][i] = -1;
            }
        }
        _wremoved[i]->SetExcluded(true);
    }

}

void CircuitActive::FindMeshCurrents() {
    Matrix C(_wremoved.size(), _wires.size());
    Matrix Z(_wires.size(), _wires.size());
    Matrix E(_wires.size(), 1);
    CalcMatrix(C, Z, E);

    auto res = (C*Z*C.Transponse()).Inv()*C*E;
    for(size_t i = 0; i < res.GetXDem(); ++i)
        _no_mono_paths[i].second = res[0][i];
}

void CircuitActive::FindCurrentsFromMesh() {
    for(auto & wire : _wires){
        double i = 0;
        for(auto & path : _no_mono_paths){
            for(size_t k = 0; k < path.first.size()-1; ++k){
                if(path.first[k] == wire.GetIndex1() && path.first[k+1] == wire.GetIndex2())
                    i += path.second;
                else if (path.first[k] == wire.GetIndex2() && path.first[k+1] == wire.GetIndex1())
                    i -= path.second;
            }
        }
        wire.SetI(i);
    }
}

bool CircuitActive::IsMonoTree() {
    std::vector<int> visited;
    std::deque<Point> deq;
    auto point = _points[0];
    do{
        bool is_next_point = false;
        for(auto elem : point.GetAllElements()){
            if(     std::find(visited.begin(), visited.end(), elem.first->GetIndex()) == visited.end()
                && !elem.second->IsExcluded()){
                point = *elem.first;
                deq.push_back(point);
                visited.push_back(point.GetIndex());
                is_next_point = true;
                break;
            }
        }
        if (!is_next_point){
            point = deq.back();
            deq.pop_back();
        }

    } while(!deq.empty());
    for(const auto& point1 : _points) {
        if(std::find(visited.begin(), visited.end(), point1.GetIndex()) == visited.end())
            return false;
    }
    return true;
}

std::vector<int> CircuitActive::FindNoMonoTreePath(Wire start) {
    std::vector<Wire*> wvisited;
    std::deque<Point> deq;
    auto it = find_if(_points.begin(), _points.end(), [&start] (const Point& element) { return element.GetIndex() == start.GetIndex1(); } );
    auto point = *it;
    deq.push_back(point);
    do{
        bool is_next_point = false;
        for(auto elem : point.GetAllElements()){
            if(    std::find(wvisited.begin(), wvisited.end(), elem.second) == wvisited.end()
                && !elem.second->IsExcluded()){
                point = *elem.first;
                deq.push_back(point);
                wvisited.push_back(elem.second);
                is_next_point = true;
                break;
            }
        }
        if (!is_next_point){
            deq.pop_back();
            point = deq.back();
        }
    } while(deq.front().GetIndex() != deq.back().GetIndex() || deq.size() < 2);

    std::vector<int> ret;
    ret.reserve(deq.size());
    for(auto & elem : deq){
        ret.emplace_back(elem.GetIndex());
    }

    return ret;
}
