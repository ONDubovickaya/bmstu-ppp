#!/bin/bash
#SBATCH --job-name="myPINGwait"
#SBATCH --partition=debug
#SBATCH --nodes=10
#SBATCH --time=0-00:01:00
#SBATCH --ntasks-per-node=1
#SBATCH --mem=1992

mpirun -np 10 ping_wait
