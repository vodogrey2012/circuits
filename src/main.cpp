#include <iostream>
#include "Wire.h"
#include "Circuit.h"
#include "CircuitActive.h"
#include <complex>

#ifndef GTEST

    int main(int argc, char* argv[]) {
        using T = std::complex<double>;

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