/**
 * @file    connect-server-demo.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

// MPI Libraries
#include <mpi.h>

using namespace std;

// Application Name
std::string application_name = "connect-server-demo";

// Global Variables
std::vector<std::string> ports;
const std::string service_name = "connect-server";

MPI_Comm intercomm;

int main( int argc, char* argv[] )
{
    // Print Entry
    std::cout << application_name << " : Starting" << std::endl;

    // Misc Variables
    char temp_cstr[MPI_MAX_PORT_NAME];
    int mpi_error;
    
    // Initialize MPI
    int mpi_thread_required = MPI_THREAD_MULTIPLE;
    int mpi_thread_provided;
    MPI_Init_thread( &argc, 
                     &argv, 
                     mpi_thread_required, 
                     &mpi_thread_provided );


    // Open the MPI Port
    mpi_error = MPI_Open_port( MPI_INFO_NULL, temp_cstr );
    if( mpi_error != MPI_SUCCESS ){
        std::cerr << "error: " << mpi_error << ", File: " << __FILE__ << ", Line: " << __LINE__ << std::endl;
        return 1;
    }
    ports.push_back( temp_cstr );

    // Publish Name
    std::cout << application_name << " : Publishing Name" << std::endl;
    MPI_Publish_name(service_name.c_str(), MPI_INFO_NULL, ports.front().c_str());
    
    // Accept the Connection
    std::cout << application_name << " : Accepting the connection" << std::endl;
    MPI_Comm_accept(ports.front().c_str(), MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm );

    // Wait
    std::cout << application_name << " : Waiting" << std::endl;
    sleep(5);

    // Unpublish the name
    std::cout << application_name << " : Unpublishing Name" << std::endl;
    MPI_Unpublish_name(service_name.c_str(), MPI_INFO_NULL, ports.front().c_str());
    
    // Finalize MPI
    MPI_Finalize();

    // Log Exit
    std::cout << application_name << " : Exiting" << std::endl;
    
    return 0;
}

