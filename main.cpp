#include <iostream>
#include "src/Wire.h"
#include "src/Circuit.h"
#include "src/CircuitActive.h"


int main() {
    CircuitActive circuit;
    std::vector<Wire> wires;
    Wire wire(0, 0, 0, 0);

    wire = Wire(0, 1, 15, 0);
    circuit.AddWire(wire);

    wire = Wire(1, 2, 0, 10);
    circuit.AddWire(wire);

    wire = Wire(0, 3, 29, 0);
    circuit.AddWire(wire);

    wire = Wire(3, 4, 9, 0);
    circuit.AddWire(wire);

    wire = Wire(4, 2, 0, 36);
    circuit.AddWire(wire);

    wire = Wire(0, 5, 22, 0);
    circuit.AddWire(wire);

    wire = Wire(5, 6, 39, 0);
    circuit.AddWire(wire);

    wire = Wire(6, 2, 0, -27);
    circuit.AddWire(wire);

    wire = Wire(5, 7, 19, 0);
    circuit.AddWire(wire);

    wire = Wire(7, 2, 25, 0);
    circuit.AddWire(wire);

    wire = Wire(5, 8, 30, 0);
    circuit.AddWire(wire);

    wire = Wire(8, 2, 0, 26);
    circuit.AddWire(wire);

    circuit.ConnectWires();

    auto res = circuit.FindCurrent(0, 1);

    std::cout << res << std::endl;

    return 0;
}
