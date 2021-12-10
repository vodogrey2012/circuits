//
// Created by Yauheni Sharamed on 07.11.2021.
//

#include "Point.h"

Wire Point::GetWireByIndex(int index2){
    std::vector<pPElement>::iterator it;
    it = std::find_if(pw_elements_.begin(), pw_elements_.end(),
                      [&index2](const pPElement &element) { return element.first->GetIndex() == index2; });
    return *(*it).second;
}

void Point::RemoveElementByIndex(int index){
    std::vector<pPElement>::iterator it;
    it = std::find_if(pw_elements_.begin(), pw_elements_.end(),
                      [&index](const pPElement &element) { return element.first->GetIndex() == index; });
    pw_elements_.erase(it);
}

Point Point::GetPointByIndex(int index2) {
    std::vector<pPElement>::iterator it;
    it = std::find_if(pw_elements_.begin(), pw_elements_.end(),
                      [&index2](const pPElement &element) { return element.first->GetIndex() == index2; });
    return *(*it).first;
}


