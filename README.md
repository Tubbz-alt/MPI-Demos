
MPI Demos
=========

A collection of MPI demo programs to show various functionality.

####Disclaimer####
This is proof-of-concept only.  Do not expect this to scale well or work in any production scale.

spawn-demo
----------

Takes an initial executable and spawns 3 other executables using `MPI_Comm_spawn` .
In addition, starts a signal handler such that if a program seg faults, then it will catch it, 
sending back a message to the main executable to have it respawn it.

####Usage Instructions####

    #  Run Spawn Demo
    ./scripts/run-spawn-demo.sh

Software Requirements
---------------------

+ __mpich__
+ __pthreads__



Compiling Demo Code
-------------------

    ./build.sh

