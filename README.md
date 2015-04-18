
MPI Demos
=========

A collection of MPI demo programs to show various functionality.

spawn-demo
----------

Takes an initial executable and spawns 3 other executables using _MPI\_Comm\_spawn__.
In addition, starts a signal handler such that if a program seg faults, then it will catch it, 
sending back a message to the main executable to have it respawn it.

