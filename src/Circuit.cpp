//
// Created by Yauheni Sharamed on 07.11.2021.
//

#include "Circuit.h"

void Circuit::AddPoints() {
    for(auto & wire : wires_) {
        Point point1(wire.GetIndex1());
        Point point2(wire.GetIndex2());
        points_.push_back(point1);
        points_.push_back(point2);
    }
}

int Circuit::ConnectWires() {
    AddPoints();
    UniquePoints();
    for(auto & wire : wires_){
        auto index1 = wire.GetIndex1();
        auto index2 = wire.GetIndex2();
        auto itp1 = find_if(points_.begin(), points_.end(), [&index1] (const Point& element) { return element.GetIndex() == index1; } );
        auto itp2 = find_if(points_.begin(), points_.end(), [&index2] (const Point& element) { return element.GetIndex() == index2; } );
        itp1->AddElement(&(*itp2), &wire);
        itp2->AddElement(&(*itp1), &wire);
    }
    return 0;
}

void Circuit::UniquePoints() {
    std::sort(points_.begin(), points_.end(), [](Point & p1, Point & p2){return p1.GetIndex() < p2.GetIndex();});
    points_.erase(unique(points_.begin(), points_.end() ), points_.end() );
}

std::ostream &operator<<(std::ostream &os, const Circuit &circuit) {
    for(Point point : circuit.points_){
        for(auto & elem : point.GetAllElements()){
            os << "* Point " << point.GetIndex() << " connected with point " <<  elem.first->GetIndex() << std::endl
                << "  with wire " << elem.second->GetIndex1() << "-" << elem.second->GetIndex2() << std::endl
                << "  R = " << elem.second->GetR() << ", E = " << elem.second->GetE() << std::endl;
        }
    }
    return os;
}
