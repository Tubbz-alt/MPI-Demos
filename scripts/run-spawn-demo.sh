#!/bin/sh

#  Set our MPI Arguments
MPI_ARGS='-envall'

#  Set our EXE
EXE=./release/bin/spawn-demo

#  Run MPI 
mpiexec ${MPI_ARGS} -n 1 ${EXE} 

