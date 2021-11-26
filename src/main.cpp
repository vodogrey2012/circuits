#include <iostream>
#include "Wire.h"
#include "Circuit.h"
#include "CircuitActive.h"

#ifdef GTEST
    #include "../tests/env/TestMain.h"
    int test_main(int argc, char* argv[]) {
#else
    int main(int argc, char* argv[]) {
#endif
    if((argc != 2) && (argc != 1)){
        std::cerr << "Arguments: infile. Or redirect stream" << std::endl;
        exit(-1);
    }

    CircuitActive circuit;

    if(argc == 2){
        std::ifstream t(argv[1]);
        if(t){
            circuit.ReadFromFile(t);
        }
        else{
            std::cerr << "Given circuit-file doesn't exist: " << argv[1] << std::endl;
            return -1;
        }
    }
    else if(argc == 1){
        circuit.ReadFromFile(std::cin);
    }


    auto res = circuit.FindCurrent();

    return res;
}