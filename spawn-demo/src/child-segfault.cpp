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
#include "../../common/String_Utilities.hpp"
#include "Spawn_Demo_Common.hpp"

using namespace std;

// Application Name
const std::string application_name = "Segfault Child  ";

/**
 * Main Function
 */
int main( int argc, char* argv[] )
{

    // Register the Segfault Handler
    signal(SIGSEGV, Segmentation_Fault_Handler );

    // Set the sleep count
    int sleep_count = 1;

    // Get the mode
    int mode = str2num<int>(argv[1]);

    // Initialize MPI
    int mpi_thread_provided;
    int mpi_thread_required = MPI_THREAD_MULTIPLE;
    MPI_Init_thread( &argc, &argv, mpi_thread_required, &mpi_thread_provided );
    
    // Print Entry
    std::cout << application_name << " : Starting" << std::endl;

    sleep(sleep_count);

    // Create a seg fault
    if( mode == 0 ){
        char* array = NULL;
        array[400] = 10;
    }

    // Finalize MPI
    MPI_Finalize();

    // End of Persistent Child
    std::cout << application_name << " : Completed gracefully." << std::endl;



    return 0;
}


