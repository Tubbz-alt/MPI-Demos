/**
 * @file    Spawn_Demo_Common.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#include "Spawn_Demo_Common.hpp"


// C++ Standard Libraries
#include <cstdlib>
#include <iostream>

// MPI Libraries
#include <mpi.h>

using namespace std;

/**
 * Segfault Handler
 */
void Segmentation_Fault_Handler( int seg )
{

    // Print Output
    std::cout << "Segmentation Fault Detected" << std::endl;

    // Check if MPI Initialized
    int mpi_initialized;
    MPI_Initialized( &mpi_initialized );

    if( mpi_initialized == true ){
        std::cout << "MPI Initialized, exiting gracefully." << std::endl;
        MPI_Finalize();
        std::exit(0);
    }
    
    // Exit
    std::exit(1);
}


