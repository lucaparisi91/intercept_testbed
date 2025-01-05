#!/bin/bash

# Slurm job options (job-name, compute nodes, job time)
#SBATCH --job-name=ior_small
#SBATCH --time=0:05:0
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --partition=standard
#SBATCH --qos=short

export SRUN_CPUS_PER_TASK=$SLURM_CPUS_PER_TASK
source env.sh
export LD_LIBRARY_PATH=$(pwd)/lib:$LD_LIBRARY_PATH

srun ./test