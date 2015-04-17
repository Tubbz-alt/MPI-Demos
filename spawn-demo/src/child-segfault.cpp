/**
 * @file    child-segfault.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#include <iostream>
#include <signal.h>
#include <unistd.h>

// MPI Libraries
#include <mpi.h>

// Utilities
#include "Spawn_Demo_Common.hpp"

using namespace std;

/**
 * Main Function
 */
int main( int argc, char* argv[] )
{
    // Register the Segfault Handler
    signal(SIGSEGV, Segmentation_Fault_Handler );

    // Set the sleep count
    int sleep_count = 1;

    // Initialize MPI
    int mpi_thread_provided;
    int mpi_thread_required = MPI_THREAD_MULTIPLE;
    MPI_Init_thread( &argc, &argv, mpi_thread_required, &mpi_thread_provided );
    
    // Print Entry
    std::cout << "Start of Segfault Child" << std::endl;

    sleep(sleep_count);

    // Create a seg fault
    char* array = NULL;
    array[400] = 10;

    // Finalize MPI
    MPI_Finalize();

    // End of Persistent Child
    std::cout << "End of Temporary Child" << std::endl;



    return 0;
}


