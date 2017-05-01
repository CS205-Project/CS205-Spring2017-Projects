Overview of tests:


These tests are for testing the building evacuation of 1000-20000 people using Dijkstra's algorithm
to calculate the nearest exit for everyone and then using simulated annealing to move people to the 
least congested exits. It also uses MPI to communicate between threads for parallel runs of simulated annealing. 

Note: all these tests run on 4 cores. You can modify the number of cores in the
build.sh file followed by a change to the constant CORES in the dijkstra.c file.

Arrangement of files:
build_mpiX.sh is the build script for the test file with X people. It used dijkstraX.c to create
a binary and uses the graph gX.txt.

How to run:
1) run ./build_mpiX.sh where X=1000, 5000, 10000, 15000, 20000
