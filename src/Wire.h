//
// Created by Yauheni Sharamed on 07.11.2021.
//

#ifndef CIRCUITS_WIRE_H
#define CIRCUITS_WIRE_H


class Wire{
public:
    Wire(int index1, int index2, double r, double e):
                _index1(index1),
                _index2(index2),
                _r(r),
                _e(e),
                _i(0){};
    Wire(double r, double e):
            _r(r),
            _e(e),
            _index1(-1),
            _index2(-1),
            _i(0){};
    int GetIndex1()    const    {   return _index1;}
    int GetIndex2()    const    {   return _index2;}
    double GetR()      const    {   return _r;     }
    double GetE()      const    {   return _e;     }
    double GetI()      const    {   return _i;     }
    void SetIndex1(int index1)  {   _index1 = index1;}
    void SetIndex2(int index2)  {   _index2 = index2;}
    void SetR(double r)         {   _r = r;}
    void SetE(double e)         {   _e = e;}
    void SetI(double i)         {   _i = i;}
    bool IsExcluded() const     {   return _is_excluded;}
    void SetExcluded(bool ex)   {    _is_excluded = ex; }
private:
    bool _is_excluded = false;
    int _index1;
    int _index2;
    double _r;
    double _e;
    double _i;
};


#endif //CIRCUITS_WIRE_H
