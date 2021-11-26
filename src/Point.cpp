//
// Created by Yauheni Sharamed on 07.11.2021.
//

#include "Point.h"

Wire Point::GetWireByIndex(int index2){
    std::vector<pPElement>::iterator it;
    it = std::find_if(_pw_elements.begin(), _pw_elements.end(),
                      [&index2](const pPElement &element) { return element.first->GetIndex() == index2; });
    return *(*it).second;
}

void Point::RemoveElementByIndex(int index){
    std::vector<pPElement>::iterator it;
    it = std::find_if(_pw_elements.begin(), _pw_elements.end(),
                      [&index](const pPElement &element) { return element.first->GetIndex() == index; });
    _pw_elements.erase(it);
}

Point Point::GetPointByIndex(int index2) {
    std::vector<pPElement>::iterator it;
    it = std::find_if(_pw_elements.begin(), _pw_elements.end(),
                      [&index2](const pPElement &element) { return element.first->GetIndex() == index2; });
    return *(*it).first;
}


