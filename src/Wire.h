//
// Created by Yauheni Sharamed on 07.11.2021.
//

#ifndef CIRCUITS_WIRE_H
#define CIRCUITS_WIRE_H


class Wire{
public:
    Wire(int index1, int index2, double r, double e, int windex):
            index1_(index1),
            index2_(index2),
            r_(r),
            e_(e),
            i_(0),
            windex_(windex){};
    Wire(double r, double e):
            r_(r),
            e_(e),
            index1_(-1),
            index2_(-1),
            windex_(0),
            i_(0){};
    int GetIndex1()    const    {   return index1_;}
    int GetIndex2()    const    {   return index2_;}
    int GetWindex()    const    {   return windex_;}
    double GetR()      const    {   return r_;     }
    double GetE()      const    {   return e_;     }
    double GetI()      const    {   return i_;     }
    void SetIndex1(int index1)  { index1_ = index1;}
    void SetIndex2(int index2)  { index2_ = index2;}
    void SetWindex(int windex)  { windex_ = windex;}
    void SetR(double r)         { r_ = r;}
    void SetE(double e)         { e_ = e;}
    void SetI(double i)         { i_ = i;}
    bool IsExcluded() const     {   return is_excluded_;}
    void SetExcluded(bool ex)   { is_excluded_ = ex; }
private:
    bool is_excluded_ = false;
    int index1_;
    int index2_;
    double r_;
    double e_;
    double i_;
    int windex_;
};


#endif //CIRCUITS_WIRE_H
