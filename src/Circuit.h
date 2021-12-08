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
    ~Circuit()= default;
    void AddWire(Wire wire){        _wires.push_back(wire);}
    int ConnectWires();
    friend std::ostream& operator<<(std::ostream& os, const Circuit& circuit);
protected:
    void UniquePoints();
    std::vector<Point> _points;
    std::vector<Wire> _wires;
    void AddPoints();
    void AddPoint(const Point& point){     _points.push_back(point);}
};


#endif //CIRCUITS_CIRCUIT_H
