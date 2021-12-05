# Status
First iteration

[![Tests](https://github.com/vodogrey2012/circuits/actions/workflows/cmake.yml/badge.svg)](https://github.com/vodogrey2012/circuits/actions/workflows/cmake.yml)

# About
This program calculates the active electrical circuit.
The input file contains a chain in the format:
```
p1 - p2, r; e;
```
or
```
p1 - p2, r; e;
```
(i.e. source voltage is optional).

The executable file takes the first required argument - the input file and a couple of optional - the points between which it is necessary to calculate the current:
```
infile <p1> <p2>
```

Test files (e2e tests) can be found [here](https://github.com/vodogrey2012/circuits/tree/master/tests/e2e).

# Base idea
Core of calculation is based on mesh tree method ([wiki](https://en.wikipedia.org/wiki/Mesh_analysis)).

Additionally, processing of parallel connections is implemented, i.e. input data like:
```
... p1 -- p2, r1; e1; p1 -- p2, r2; e2; ...
```
is also valid. 
