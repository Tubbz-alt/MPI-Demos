
MPI Demos
=========

A collection of MPI demo programs to show various functionality.

####Disclaimer####
This is proof-of-concept only.  Do not expect this to scale well or work in any production scale.


connect-demo
------------

Creates several running sessions and connects them via the hydra nameserver.

More information can be found [here][https://wiki.mpich.org/mpich/index.php/Using_the_Hydra_Process_Manager#Name_Publishing].


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

The demo comes with an integrated build script which should be used before branching out on your own.

To see the help/usage, run

    ./build.sh -h

    usage: ./build.sh <flags>

    -h | --help    : Print usage instructions.
    -m             : Build software.
    -c             : Clean software.

By default, the build script will make the software. 

