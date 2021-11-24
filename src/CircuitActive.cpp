//
// Created by Yauheni Sharamed on 20.11.2021.
//

#include "CircuitActive.h"

double CircuitActive::FindCurrent(int i1, int i2) {
    static bool is_calculated = false;

    if(!is_calculated){
        TreePreProc();
        FindMaxTree();
        FindMeshCurrents();
        TreePostProc();
        FindCurrentsFromMesh();
    }
    is_calculated = true;

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

void CircuitActive::CalcMatrix(Matrix<int> & C, Matrix<double> & Z, Matrix<double> & E) {
    for(size_t i = 0; i < E.GetIDem(); ++i){
        Z[i][i] = _wires[i].GetR();
    }

    for(size_t i = 0; i < C.GetIDem(); ++i){
        _wremoved[i]->SetExcluded(false);
        auto path = FindNoMonoTreePath(*_wremoved[i]);

        //for(auto & r : path)
        //    std::cout << r ;
        //std::cout << std::endl;

        _no_mono_paths.emplace_back(std::make_pair(path, 0));
        for(size_t j = 0; j < C.GetJDem(); ++j){
            for(size_t k = 0; k < path.size()-1; ++k){
                if(path[k] == _wires[j].GetIndex1() && path[k+1] == _wires[j].GetIndex2()) {
                    C[i][j] = 1;
                    E[j][0] = _wires[j].GetE();
                }
                else if (path[k] == _wires[j].GetIndex2() && path[k+1] == _wires[j].GetIndex1()){
                    C[i][j] = -1;
                    E[j][0] = _wires[j].GetE();
                }
            }
        }
        _wremoved[i]->SetExcluded(true);
    }

}

void CircuitActive::FindMeshCurrents() {
    Matrix<int>    C(_wremoved.size(), _wires.size());
    Matrix<double> Z(_wires.size(), _wires.size());
    Matrix<double> E(_wires.size(), 1);
    CalcMatrix(C, Z, E);

    //std::cout << C << std::endl;
    //std::cout << Z << std::endl;
    //std::cout << E << std::endl;

    auto res = (Matrix<double>(C)*Z*Matrix<double>(C.Transponse())).Inv()*Matrix<double>(C)*E;
    for(size_t i = 0; i < res.GetIDem(); ++i)
        _no_mono_paths[i].second = res[i][0];
    //std::cout << res << std::endl;

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

void CircuitActive::ReadFromFile(const std::string& filename){
    std::ifstream t(filename);
    if(!t){
        std::cerr << "Given circuit-file doesn't exist." << std::endl;
        exit(-1);
    }

    std::stringstream ss;
    ss << t.rdbuf();
    std::string s = ss.str();

    std::string point1("(\\d+)");
    std::string point2("(\\d+)");
    std::string resist("(\\d+(?:\\.\\d+)?)");
    std::string opteds("(?:(-?\\d+(?:\\.\\d+)?)\\s*;)?");

    std::regex word_regex(point1 + "\\s*--\\s*" + point2 + "\\s*,\\s*" + resist + "\\s*;\\s*" + opteds);
    auto words_begin =
            std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    if(words_begin == words_end){
        std::cerr << "Incorrect input file format." << std::endl;
        exit(-1);
    }

    for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;

        int index1 = std::stoi(match[1]);
        int index2 = std::stoi(match[2]);
        double r = std::stof(match[3]);
        double e;
        if(match[4].str().length() != 0)
            e = std::stod(match[4].str());
        else
            e = 0;
        this->AddWire(Wire(index1, index2, r, e));
    }
}

void CircuitActive::TreePreProc() {
    for(auto & wire : _wires){
        if(wire.GetIndex1() > wire.GetIndex2()){
            auto si1 = wire.GetIndex1();
            wire.SetIndex1(wire.GetIndex2());
            wire.SetIndex2(si1);
            wire.SetE(wire.GetE()*(-1.0));
        }
    }

    std::sort(_wires.begin(),_wires.end(),
              [](Wire & w1, Wire & w2){
        return w1.GetIndex1() == w2.GetIndex1() ? w1.GetIndex2() < w2.GetIndex2() : w1.GetIndex1() < w2.GetIndex2();
    });

    std::vector<Wire>::iterator it;
    int i = -1;
    do {
        it = std::adjacent_find(_wires.begin(), _wires.end(),
                                [](Wire &w1, Wire &w2) {
                                    return (w1.GetIndex1() == w2.GetIndex1()) && (w1.GetIndex2() == w2.GetIndex2());
                                });
        if(it == _wires.end())
            break;

        Wire wire(i, it->GetIndex2(), 0, 0);
        AddWire(wire);
        it->SetIndex2(i);
        Point point(i);
        i -= 1;
    } while(it != _wires.end());

    for(auto & point : _points){
        point.ResetConnections();
    }
    ConnectWires();
}

void CircuitActive::TreePostProc() {
    for(auto & path : _no_mono_paths){
        auto & path_vec = path.first;

        std::vector<int>::iterator it;
        for( it = std::find_if(path_vec.begin(), path_vec.end(),
            [](const int &element) { return element < 0; });
             it != path_vec.end();
             it = std::find_if(path_vec.begin(), path_vec.end(),
            [](const int &element) { return element < 0; }) ){
            path_vec.erase(it);
        }

        //for(auto & r : path.first)
        //    std::cout << r ;
        //std::cout << std::endl;
    }

}
