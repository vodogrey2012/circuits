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
        std::cout << p1 << " -- " << p2 << ":\tI = "
                  << circuit.FindCurrent(p1, p2) << std::endl;
    }

    return 0;
}
