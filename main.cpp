#include <iostream>
#include "src/Wire.h"
#include "src/Circuit.h"
#include "src/CircuitActive.h"


int main() {
    CircuitActive circuit;

    circuit.ReadFromFile("../test_circuit.txt");

    circuit.ConnectWires();

    auto res = circuit.FindCurrent(0, 1);

    std::cout << res << std::endl;

    return 0;
}
