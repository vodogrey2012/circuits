#include <iostream>
#include "src/Wire.h"
#include "src/Circuit.h"
#include "src/CircuitActive.h"


int main(int argc, char* argv[]) {
    if((argc != 4) && (argc != 2)){
        std::cerr << "Arguments: infile [p1] [p2]." << std::endl;
        exit(-1);
    }

    CircuitActive circuit;
    circuit.ReadFromFile(argv[1]);
    circuit.ConnectWires();

    if(argc == 4){
        std::cout << std::stoi(argv[2]) << " -- " << std::stoi(argv[3]) << ":\tI = "
                  << circuit.FindCurrent(std::stoi(argv[2]), std::stoi(argv[3])) << std::endl;
    }
    else {
        int p1 = 0;
        int p2 = 1;
        std::cout << p1 << " -- " << p2 << ":\tI = "
                  << circuit.FindCurrent(p1, p2) << std::endl;
    }

    return 0;
}
