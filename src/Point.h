//
// Created by Yauheni Sharamed on 07.11.2021.
//

#ifndef CIRCUITS_POINT_H
#define CIRCUITS_POINT_H

#include "Wire.h"
#include <vector>
#include <algorithm>

template <typename T>
class Point{
public:
    typedef std::pair<Point*, Wire<T>*> pPElement;
    Point():
            index_(0){};
    Point(int index):
            index_(index){};
    Point(int index, Point* point, Wire<T>* wire):
            index_(index){  pw_elements_.emplace_back(point, wire);}
    std::vector<pPElement> GetAllElements(){    return pw_elements_;}
    void ResetConnections(){    pw_elements_.clear();}
    void AddElement(Point* point, Wire<T>* wire){  pw_elements_.emplace_back(point, wire);}
    int GetIndex() const{       return index_;}
    friend bool operator== (const Point &p1, const Point &p2){ return (p1.GetIndex() == p2.GetIndex() ); }

    Wire<T> GetWireByIndex(int index2){
        typename std::vector<pPElement>::iterator it;
        it = std::find_if(pw_elements_.begin(), pw_elements_.end(),
                          [&index2](const pPElement &element) { return element.first->GetIndex() == index2; });
        return *(*it).second;
    }

    void RemoveElementByIndex(int index){
        typename std::vector<pPElement>::iterator it;
        it = std::find_if(pw_elements_.begin(), pw_elements_.end(),
                          [&index](const pPElement &element) { return element.first->GetIndex() == index; });
        pw_elements_.erase(it);
    }

    Point GetPointByIndex(int index2) {
        typename std::vector<pPElement>::iterator it;
        it = std::find_if(pw_elements_.begin(), pw_elements_.end(),
                          [&index2](const pPElement &element) { return element.first->GetIndex() == index2; });
        return *(*it).first;
    }

private:
    int index_;
    std::vector<pPElement> pw_elements_;
};

#endif //CIRCUITS_POINT_H
