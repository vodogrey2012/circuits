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
    if((argc != 4) && (argc != 2)){
        std::cerr << "Arguments: infile [p1] [p2]." << std::endl;
        exit(-1);
    }

    CircuitActive circuit;
    circuit.ReadFromFile(argv[1]);

    if(argc == 4){
        int p1;
        int p2;
        std::istringstream (argv[2]) >> p1;
        std::istringstream (argv[3]) >> p2;
        std::cout << p1 << " -- " << p2 << ":\tI = "
                  << circuit.FindCurrent(p1, p2) << std::endl;
    }
    else {
        int p1 = 1;
        int p2 = 2;
        auto res = circuit.FindCurrent(p1, p2);
#ifndef DEBUG
        std::cout << p1 << " -- " << p2 << ":\tI = "
                  << res << std::endl;
#endif
    }

    return 0;
}