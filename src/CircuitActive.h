//
// Created by Yauheni Sharamed on 20.11.2021.
//

#ifndef CIRCUITS_CIRCUITACTIVE_H
#define CIRCUITS_CIRCUITACTIVE_H

#include "Circuit.h"
#include "Matrix.h"
#include <deque>
#include <fstream>
#include <string>
#include <regex>

class CircuitActive : public Circuit{
public:
    CircuitActive()= default;
    ~CircuitActive()= default;
    double FindCurrent();
    int ReadFromFile(const std::istream& sfile);
private:
    void TreePreProc();
    void TreePostProc();
    void FindMaxTree();
    bool IsMonoTree();
    void CalcMatrix(Matrix<int> & C, Matrix<double> & Z, Matrix<double> & E);
    void FindMeshCurrents();
    void FindCurrentsFromMesh();
    std::vector<int> FindNoMonoTreePath(Wire start);
    std::vector<Wire*> _wremoved;
    std::vector<std::pair<std::vector<int>, double>> _no_mono_paths;

};


#endif //CIRCUITS_CIRCUITACTIVE_H
