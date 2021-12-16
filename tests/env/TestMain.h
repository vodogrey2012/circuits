//
// Created by Yauheni Sharamed on 24.11.2021.
//

#ifndef CIRCUITS_TESTMAIN_H
#define CIRCUITS_TESTMAIN_H

#include <iostream>
#include "../../src/Wire.h"
#include "../../src/Circuit.h"
#include "../../src/CircuitActive.h"
#include <complex>

#ifdef GTEST

template<typename T>
int test_main(int argc, char* argv[]) {
    if((argc != 2) && (argc != 1)){
        std::cerr << "Arguments: infile. Or redirect stream" << std::endl;
        return -1;
    }

    CircuitActive<T> circuit;

    if(argc == 2){
        std::ifstream t(argv[1]);
        if(t){
            if(circuit.ReadFromFile(t)) return -1;
        }
        else{
            std::cerr << "Given circuit-file doesn't exist: " << argv[1] << std::endl;
            return -1;
        }
    }
    else {
        circuit.ReadFromFile(std::cin);
    }

    int res = circuit.FindCurrent();

    return res;
}
#endif

#endif //CIRCUITS_TESTMAIN_H
