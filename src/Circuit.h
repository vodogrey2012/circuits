//
// Created by Yauheni Sharamed on 07.11.2021.
//

#ifndef CIRCUITS_CIRCUIT_H
#define CIRCUITS_CIRCUIT_H

#include "Point.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>


class Circuit {
public:
    Circuit();
    void AddWire(Wire wire);
    void ConnectWires();
    void ReadFromFile(const std::string& filename);
    friend std::ostream& operator<<(std::ostream& os, const Circuit& circuit);
protected:
    void UniquePoints();
    std::vector<Point> _points;
    std::vector<Wire> _wires;
    void AddPoints();
};


#endif //CIRCUITS_CIRCUIT_H
