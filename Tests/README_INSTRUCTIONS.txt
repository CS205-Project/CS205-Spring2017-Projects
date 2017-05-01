Overview of tests:


These tests are testing building evacuation of 1000-20000 people in a building using Dijkstra's algorithm
to calculate the nearest exit for everyone and then using simulated annealing to move people to the 
right exit to avoid congestion. It also uses MPI to communicate between threads for more efficient
simulated annealing. 

Note: all these tests run on 4 cores. You can change the number of cores in the
build.sh file but then you also have to change the constant CORES in the dijkstra.c file.

Arrangement of files:
build_mpiX.sh is the build script for the test file with X people. It used dijkstraX.c to create
a binary and uses the graph gX.txt.

How to run:
1) run ./build_mpiX.sh where X=1000, 5000, 10000, 15000, 20000
