//
// Created by Yauheni Sharamed on 07.11.2021.
//

#include "Wire.h"

Wire::Wire(int index1, int index2, double r, double e){
    _index1 = index1;
    _index2 = index2;
    _r = r;
    _e = index2 > index1 ? -1.0*e : e;
}

Wire::Wire(double r, double e){
    _r = r;
    _e = e;
}

int Wire::GetIndex1()      const   {   return _index1;}
int Wire::GetIndex2()      const   {   return _index2;}
double Wire::GetR()        const   {   return _r;     }
double Wire::GetE()        const   {   return _e;     }
void Wire::SetIndex1(int index1)   { _index1 = index1;}
void Wire::SetIndex2(int index2)   { _index2 = index2;}
void Wire::SetR(double r)          { _r = r;}
void Wire::SetE(double e)          { _e = _index2 > _index1 ? -1.0 * e : e;}

bool Wire::IsExcluded() const {
    return _is_exluded;
}

void Wire::SetExcluded(bool ex) {
    _is_exluded = ex;
}

void Wire::SetI(double i) {
    _i = i;
}

double Wire::GetI() const {
    return _i;
}


