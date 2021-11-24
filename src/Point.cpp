//
// Created by Yauheni Sharamed on 07.11.2021.
//

#include "Point.h"


Point::Point(int index, Point* point, Wire* wire){
    _index = index;
    _pw_elements.emplace_back(point, wire);
}

Point::Point(int index) {
    _index = index;
}

Point::Point() {
    _index = 0;
}

Wire Point::GetWireByIndex(int index2){
    std::vector<pPElement>::iterator it;
    it = std::find_if(_pw_elements.begin(), _pw_elements.end(),
                      [&index2](const pPElement &element) { return element.first->GetIndex() == index2; });
    return *(*it).second;
}

void Point::AddElement(Point* point, Wire* wire) {
    _pw_elements.emplace_back(point, wire);
}

void Point::RemoveElementByIndex(int index){
    std::vector<pPElement>::iterator it;
    it = std::find_if(_pw_elements.begin(), _pw_elements.end(),
                      [&index](const pPElement &element) { return element.first->GetIndex() == index; });
    _pw_elements.erase(it);
}

int Point::GetIndex() const {
    return _index;
}

std::vector<Point::pPElement> Point::GetAllElements() {
    return _pw_elements;
}

Point Point::GetPointByIndex(int index2) {
    std::vector<pPElement>::iterator it;
    it = std::find_if(_pw_elements.begin(), _pw_elements.end(),
                      [&index2](const pPElement &element) { return element.first->GetIndex() == index2; });
    return *(*it).first;
}

void Point::ResetConnections() {
    _pw_elements.clear();
}

