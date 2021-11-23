#include <iostream>
#include "src/Wire.h"
#include "src/Circuit.h"
#include "src/CircuitActive.h"


int main(int argc, char* argv[]) {
    if(argc != 2){
        std::cerr << "No input file provided!" << std::endl;
        exit(-1);
    }

    CircuitActive circuit;
    circuit.ReadFromFile(argv[1]);
    circuit.ConnectWires();

    auto res = circuit.FindCurrent(0, 1);

    std::cout << res << std::endl;
    return 0;
}
