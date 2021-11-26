//
// Created by Yauheni Sharamed on 07.11.2021.
//

#include "Circuit.h"

void Circuit::AddPoints() {
    for(auto & wire : _wires) {
        Point point1(wire.GetIndex1());
        Point point2(wire.GetIndex2());
        _points.push_back(point1);
        _points.push_back(point2);
    }
}

int Circuit::ConnectWires() {
    AddPoints();
    UniquePoints();
    for(auto & wire : _wires){
        auto index1 = wire.GetIndex1();
        auto index2 = wire.GetIndex2();
        if(index1 == index2){
            std::cerr << "Error! Wire indexes equals!" << std::endl;
            return -1;
        }
        auto itp1 = find_if(_points.begin(), _points.end(), [&index1] (const Point& element) { return element.GetIndex() == index1; } );
        auto itp2 = find_if(_points.begin(), _points.end(), [&index2] (const Point& element) { return element.GetIndex() == index2; } );
        itp1->AddElement(&(*itp2), &wire);
        itp2->AddElement(&(*itp1), &wire);
    }
    return 0;
}

void Circuit::UniquePoints() {
    std::sort(_points.begin(),_points.end(), [](Point & p1, Point & p2){return p1.GetIndex() < p2.GetIndex();});
    _points.erase( unique( _points.begin(), _points.end() ), _points.end() );
}

std::ostream &operator<<(std::ostream &os, const Circuit &circuit) {
    for(Point point : circuit._points){
        for(auto & elem : point.GetAllElements()){
            os << "* Point " << point.GetIndex() << " connected with point " <<  elem.first->GetIndex() << std::endl
                << "  with wire " << elem.second->GetIndex1() << "-" << elem.second->GetIndex2() << std::endl
                << "  R = " << elem.second->GetR() << ", E = " << elem.second->GetE() << std::endl;
        }
    }
    return os;
}
