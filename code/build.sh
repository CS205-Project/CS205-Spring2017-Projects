#!/bin/bash
#SBATCH -n 64   # Number of cores requested
#SBATCH -t 10  # Runtime in minutes
#SBATCH -p seas_iacs       # Partition to submit to
#SBATCH --mem=10000      # Memory per cpu in MB (see also --mem-per-cpu)
#SBATCH --open-mode=append
#SBATCH --mail-type=END,FAIL    # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --mail-user=sonu_mehta@g.harvard.edu        # Email to which notifications will be sent
#SBATCH -o out%j.out       # Standard out goes to this file
gcc -Wall -std=c99 -D_XOPEN_SOURCE=700 -fopenmp -o dijkstra dijkstra.c
	

thread_list='1 4 16 32 64'

for thread in $thread_list
do
    echo ============================
    echo testing with $thread threads
    export OMP_NUM_THREADS=$thread
    ./dijkstra  # provide an argument to surpress serial and dgemm 
done
