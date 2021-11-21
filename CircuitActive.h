//
// Created by Yauheni Sharamed on 20.11.2021.
//

#ifndef CIRCUITS_CIRCUITACTIVE_H
#define CIRCUITS_CIRCUITACTIVE_H

#include "Circuit.h"
#include "Matrix.h"
#include <deque>

class CircuitActive : public Circuit{
public:
    double FindCurrent(int i1, int i2);
private:
    void FindMaxTree();
    bool IsMonoTree();
    void CalcMatrix(Matrix& C, Matrix& Z, Matrix& E);
    void FindMeshCurrents();
    void FindCurrentsFromMesh();
    std::vector<int> FindNoMonoTreePath(Wire start);
    std::vector<Wire*> _wremoved;
    std::vector<std::pair<std::vector<int>, double>> _no_mono_paths;

};


#endif //CIRCUITS_CIRCUITACTIVE_H
