//
// Created by Yauheni Sharamed on 07.11.2021.
//

#ifndef CIRCUITS_CIRCUIT_H
#define CIRCUITS_CIRCUIT_H

#include "Point.h"
#include <iostream>


class Circuit {
public:
    Circuit()= default;
    virtual ~Circuit()= default;
    void AddWire(Wire wire){        wires_.push_back(wire);}
    int ConnectWires();
    friend std::ostream& operator<<(std::ostream& os, const Circuit& circuit);
protected:
    void UniquePoints();
    std::vector<Point> points_;
    std::vector<Wire> wires_;
    void AddPoints();
    void AddPoint(const Point& point){     points_.push_back(point);}
};


#endif //CIRCUITS_CIRCUIT_H
