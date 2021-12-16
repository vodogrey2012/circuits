//
// Created by Yauheni Sharamed on 07.11.2021.
//

#ifndef CIRCUITS_WIRE_H
#define CIRCUITS_WIRE_H

template <typename T>
class Wire{
public:
    Wire(int index1, int index2, T r, T e, int windex):
            index1_(index1),
            index2_(index2),
            r_(r),
            e_(e),
            i_(0),
            windex_(windex){};
    Wire(T r, T e):
            r_(r),
            e_(e),
            index1_(-1),
            index2_(-1),
            windex_(0),
            i_(0){};
    int GetIndex1()    const    {   return index1_;}
    int GetIndex2()    const    {   return index2_;}
    int GetWindex()    const    {   return windex_;}
    T GetR()      const    {   return r_;     }
    T GetE()      const    {   return e_;     }
    T GetI()      const    {   return i_;     }
    void SetIndex1(int index1)  { index1_ = index1;}
    void SetIndex2(int index2)  { index2_ = index2;}
    void SetWindex(int windex)  { windex_ = windex;}
    void SetR(T r)         { r_ = r;}
    void SetE(T e)         { e_ = e;}
    void SetI(T i)         { i_ = i;}
    bool IsExcluded() const     {   return is_excluded_;}
    void SetExcluded(bool ex)   { is_excluded_ = ex; }
private:
    bool is_excluded_ = false;
    int index1_;
    int index2_;
    T r_;
    T e_;
    T i_;
    int windex_;
};


#endif //CIRCUITS_WIRE_H
