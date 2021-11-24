# Status
First iteration

[![Tests](https://github.com/watson/ci-info/workflows/Tests/badge.svg)](https://github.com/watson/ci-info/actions)

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

# Base idea
Core of calculation is based on mash tree calculation method (https://en.wikipedia.org/wiki/Mesh_analysis).

Additionally, processing of parallel connections is implemented, i.e. input data like:
```
... p1 -- p2, r1; e1; p1 -- p2, r2; e2; ...
```
is also valid. 
