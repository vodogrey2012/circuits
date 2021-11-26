//
// Created by Yauheni Sharamed on 07.11.2021.
//

#ifndef CIRCUITS_POINT_H
#define CIRCUITS_POINT_H

#include "Wire.h"
#include <vector>
#include <algorithm>

class Point{
public:
    typedef std::pair<Point*, Wire*> pPElement;
    explicit Point():
            _index(0){};
    explicit Point(int index):
            _index(index){};
    explicit Point(int index, Point* point, Wire* wire):
            _index(index){  _pw_elements.emplace_back(point, wire);}
    Wire GetWireByIndex(int index2);
    Point GetPointByIndex(int index2);
    std::vector<pPElement> GetAllElements(){    return _pw_elements;}
    void RemoveElementByIndex(int index2);
    void ResetConnections(){    _pw_elements.clear();}
    void AddElement(Point* point, Wire* wire){  _pw_elements.emplace_back(point, wire);}
    int GetIndex() const{       return _index;}
    friend bool operator== (const Point &p1, const Point &p2){ return (p1.GetIndex() == p2.GetIndex() ); }
private:
    int _index;
    std::vector<pPElement> _pw_elements;
};

#endif //CIRCUITS_POINT_H
