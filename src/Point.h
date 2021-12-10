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
    Point():
            index_(0){};
    Point(int index):
            index_(index){};
    Point(int index, Point* point, Wire* wire):
            index_(index){  pw_elements_.emplace_back(point, wire);}
    Wire GetWireByIndex(int index2);
    Point GetPointByIndex(int index2);
    std::vector<pPElement> GetAllElements(){    return pw_elements_;}
    void RemoveElementByIndex(int index2);
    void ResetConnections(){    pw_elements_.clear();}
    void AddElement(Point* point, Wire* wire){  pw_elements_.emplace_back(point, wire);}
    int GetIndex() const{       return index_;}
    friend bool operator== (const Point &p1, const Point &p2){ return (p1.GetIndex() == p2.GetIndex() ); }
private:
    int index_;
    std::vector<pPElement> pw_elements_;
};

#endif //CIRCUITS_POINT_H
