/**
 *  @file    spawn-demo.cpp
 *  @author  Marvin Smith
 *  @date    4/17/2015
 */

// C++ Standard Libraries
#include <iostream>
#include <string>
#include <unistd.h>

// MPI Libraries
#include <mpi.h>


using namespace std;

int main( int argc, char* argv[] )
{

    // Initialize Arguments
    char** temp_argv_1 = new char*[2];
    char** temp_argv_2 = new char*[2];
    temp_argv_1[0] = "1";
    temp_argv_1[1] = NULL;
    temp_argv_2[0] = "2";
    temp_argv_2[1] = NULL;

    // Initialize MPI
    int mpi_thread_provided;
    int mpi_thread_required = MPI_THREAD_MULTIPLE;
    MPI_Init_thread( &argc, &argv, mpi_thread_required, &mpi_thread_provided );

    // Start of main
    std::cout << "Starting Spawn Demo" << std::endl;

    // Spawn the Persistent Child
    int child_persistent_errcode;
    MPI_Comm child_persistent_intercomm;
    MPI_Comm_spawn( "./release/bin/child-persistent", 
                    MPI_ARGV_NULL, 
                    1, 
                    MPI_INFO_NULL, 
                    0,
                    MPI_COMM_WORLD, 
                    &child_persistent_intercomm, 
                    &child_persistent_errcode );
    
    
    // Spawn 2 Temporary Children
    int child_temporary_errcode;
    MPI_Comm child_temporary_intercomm_01;
    MPI_Comm child_temporary_intercomm_02;


    MPI_Comm_spawn( "./release/bin/child-temporary", 
                    temp_argv_1,
                    1, 
                    MPI_INFO_NULL,
                    0,
                    MPI_COMM_WORLD,
                    &child_temporary_intercomm_01, 
                    &child_temporary_errcode );
    
    // Wait for a bit 
    sleep(1);
    
    MPI_Comm_spawn( "./release/bin/child-temporary", 
                    temp_argv_2,
                    1, 
                    MPI_INFO_NULL,
                    0,
                    MPI_COMM_WORLD,
                    &child_temporary_intercomm_02, 
                    &child_temporary_errcode );

    
    // Spawn the Segfault Child
    int child_segfault_errcode;
    MPI_Comm child_segfault_intercomm;
    MPI_Comm_spawn( "./release/bin/child-segfault", 
                    MPI_ARGV_NULL, 
                    1, 
                    MPI_INFO_NULL, 
                    0,
                    MPI_COMM_WORLD, 
                    &child_segfault_intercomm, 
                    &child_segfault_errcode );


    // Wait on Persistent Child Intercommunicator
    MPI_Barrier( child_persistent_intercomm );

    // Wait on Comm World
    std::cout << "Spawn Demo Waiting at Final Barrier" << std::endl;
    MPI_Barrier( MPI_COMM_WORLD );

    // Finalize MPI
    MPI_Finalize();

    // End of Main Demo
    std::cout << "End of Spawn Demo" << std::endl;

    delete [] temp_argv_1;
    delete [] temp_argv_2;

    return 0;
}


