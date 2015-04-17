/**
 * @file    child-temporary.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#include <iostream>
#include <string>
#include <unistd.h>

// Utilities
#include "../../common/String_Utilities.hpp"

// MPI Libraries
#include <mpi.h>

using namespace std;

/**
 * @brief Main Function
 */
int main( int argc, char* argv[] )
{

    // Get the sleep count
    int sleep_count = str2num<int>(argv[1]); 

    // Initialize MPI
    int mpi_thread_provided;
    int mpi_thread_required = MPI_THREAD_MULTIPLE;
    MPI_Init_thread( &argc, &argv, mpi_thread_required, &mpi_thread_provided );
    
    // Print Entry
    std::cout << "Start of Temporary Child" << std::endl;

    sleep(sleep_count);

    // Finalize MPI
    MPI_Finalize();

    // End of Persistent Child
    std::cout << "End of Temporary Child" << std::endl;

    return 0;
}

