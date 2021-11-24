//
// Created by Yauheni Sharamed on 07.11.2021.
//

#ifndef CIRCUITS_WIRE_H
#define CIRCUITS_WIRE_H


class Wire{
public:
    Wire(int index1, int index2, double r, double e);
    Wire(double r, double e);
    int GetIndex1()    const;
    int GetIndex2()    const;
    double GetR()      const;
    double GetE()      const;
    double GetI()      const;
    void SetIndex1(int index1);
    void SetIndex2(int index2);
    void SetR(double r);
    void SetE(double e);
    void SetI(double i);
    bool IsExcluded() const;
    void SetExcluded(bool ex);
private:
    bool _is_excluded = false;
    int _index1 = -1;
    int _index2 = -1;
    double _r;
    double _e;
    double _i;
};

#endif //CIRCUITS_WIRE_H
