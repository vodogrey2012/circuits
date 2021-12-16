//
// Created by Yauheni Sharamed on 07.11.2021.
//

#ifndef CIRCUITS_CIRCUIT_H
#define CIRCUITS_CIRCUIT_H

#include "Point.h"
#include <iostream>

template <typename T>
class Circuit {
public:
    Circuit()= default;
    virtual ~Circuit()= default;
    void AddWire(Wire<T> wire){        wires_.push_back(wire);}

    int ConnectWires() {
        AddPoints();
        UniquePoints();
        for(auto & wire : wires_){
            auto index1 = wire.GetIndex1();
            auto index2 = wire.GetIndex2();
            auto itp1 = find_if(points_.begin(), points_.end(), [&index1] (const Point<T>& element) { return element.GetIndex() == index1; } );
            auto itp2 = find_if(points_.begin(), points_.end(), [&index2] (const Point<T>& element) { return element.GetIndex() == index2; } );
            itp1->AddElement(&(*itp2), &wire);
            itp2->AddElement(&(*itp1), &wire);
        }
        return 0;
    }

    std::ostream &operator<<(std::ostream &os) {
        for(Point<T> point : points_){
            for(auto & elem : point.GetAllElements()){
                os << "* Point " << point.GetIndex() << " connected with point " <<  elem.first->GetIndex() << std::endl
                   << "  with wire " << elem.second->GetIndex1() << "-" << elem.second->GetIndex2() << std::endl
                   << "  R = " << elem.second->GetR() << ", E = " << elem.second->GetE() << std::endl;
            }
        }
        return os;
    }

protected:
    void UniquePoints() {
        std::sort(points_.begin(), points_.end(), [](Point<T> & p1, Point<T> & p2){return p1.GetIndex() < p2.GetIndex();});
        points_.erase(unique(points_.begin(), points_.end() ), points_.end() );
    }

    std::vector<Point<T>> points_;
    std::vector<Wire<T>> wires_;

    void AddPoints() {
        for(auto & wire : wires_) {
            Point<T> point1(wire.GetIndex1());
            Point<T> point2(wire.GetIndex2());
            points_.push_back(point1);
            points_.push_back(point2);
        }
    }
};


#endif //CIRCUITS_CIRCUIT_H
