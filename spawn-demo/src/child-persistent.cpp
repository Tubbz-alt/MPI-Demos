/**
 * @file    child-persistent.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#include <iostream>
#include <string>
#include <unistd.h>

// MPI Libraries
#include <mpi.h>

using namespace std;

/**
 * @brief Main Function
 */
int main( int argc, char* argv[] )
{

    // Initialize MPI
    int mpi_thread_provided;
    int mpi_thread_required = MPI_THREAD_MULTIPLE;
    MPI_Init_thread( &argc, &argv, mpi_thread_required, &mpi_thread_provided );
    
    // Get Parent Communicator
    MPI_Comm parent_comm;
    MPI_Comm_get_parent( &parent_comm );

    // Print Entry
    std::cout << "Start of Persistent Child" << std::endl;

    sleep(4);

    // Wait on Parent Comm
    if( parent_comm != MPI_COMM_NULL ){
        MPI_Barrier( parent_comm );
    }

    // Wait on Comm World
    MPI_Barrier( MPI_COMM_WORLD );

    // Finalize MPI
    MPI_Finalize();

    // End of Persistent Child
    std::cout << "End of Persistent Child" << std::endl;

    return 0;
}

