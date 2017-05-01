Overview of tests:

These tests are for testing the building evacuation of 1000-20000 people using Dijkstra's algorithm
to calculate the nearest exit for everyone and then using simulated annealing to move people to the 
least congested exit. It uses MPI to communicate between threads for parallel runs of simulated annealing. 

These test outputs focus on showing how simulated annealing works by improving the solution until it reaches
an optimal solution.

Note: These tests run on 1, 2, 4, 8, 16, 32, 64 cores.

Arrangement of files:
buildX.sh is the build script for the test file with X people. It used dijkstraX.c to create
a binary and uses the graph gX.txt.

How to run:
1) run ./build_mpiX.sh where X=1000, 5000, 10000, 15000, 20000
