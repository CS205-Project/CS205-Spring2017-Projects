#!/bin/bash
#SBATCH -n 32   # Number of cores requested
#SBATCH -t 60  # Runtime in minutes
#SBATCH -p seas_iacs       # Partition to submit to
#SBATCH --mem=10000      # Memory per cpu in MB (see also --mem-per-cpu)
#SBATCH --open-mode=append
#SBATCH --mail-type=END,FAIL    # Type of email notification- BEGIN,END,FAIL,ALL
#SBATCH --mail-user=none@g.harvard.edu        # Email to which notifications will be sent
#SBATCH -o out%j.out       # Standard out goes to this file
#SBATCH -e E_%j.err
gcc -lm -Wall -std=c99 -D_XOPEN_SOURCE=700 -fopenmp -o dijkstra d.c
	

thread_list='1 2 4 8 16 32 64'

for thread in $thread_list
do
    echo ============================
    echo testing with $thread threads
    export OMP_NUM_THREADS=$thread
    ./dijkstra  # provide an argument to surpress serial and dgemm 
done
