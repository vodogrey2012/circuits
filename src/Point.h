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
    explicit Point();
    explicit Point(int index);
    explicit Point(int index, Point* point, Wire* wire);
    Wire GetWireByIndex(int index2);
    Point GetPointByIndex(int index2);
    std::vector<pPElement> GetAllElements();
    void RemoveElementByIndex(int index2);
    void ResetConnections();
    void AddElement(Point* point, Wire* wire);
    int GetIndex() const;
private:
    int _index;
    std::vector<pPElement> _pw_elements;
};


#endif //CIRCUITS_POINT_H
