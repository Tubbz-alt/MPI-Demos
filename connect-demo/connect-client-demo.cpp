/**
 * @file    connect-client-demo.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#include <iostream>
#include <string>
#include <vector>

// MPI Libraries
#include <mpi.h>

using namespace std;


// Application Name
const std::string application_name = "connect-client-demo";

// Global Variables
std::vector<std::string> ports;
MPI_Comm intercomm;

const std::string service_name = "connect-server";

/**
 * @brief Main Function
 */
int main( int argc, char* argv[] )
{

    // Misc Variables
    char temp_str[MPI_MAX_PORT_NAME];
    
    // Print Entry
    std::cout << application_name << " : Starting" << std::endl;

    // Initialize MPI
    int mpi_thread_required = MPI_THREAD_MULTIPLE;
    int mpi_thread_provided;
    MPI_Init_thread( &argc, 
                     &argv, 
                     mpi_thread_required, 
                     &mpi_thread_provided );

    // Lookup the name
    std::cout << application_name << " : Lookup Name" << std::endl;
    MPI_Lookup_name(service_name.c_str(), MPI_INFO_NULL, temp_str );
    ports.push_back(temp_str);

    // Connect
    std::cout << application_name << " : Connecting" << std::endl;
    MPI_Comm_connect ( ports.front().c_str(), MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm ); 
    

    // Disconnect
    std::cout << application_name << " : Disconnecting" << std::endl;
    MPI_Comm_disconnect( &intercomm );

    // Finalize MPI
    MPI_Finalize();
    
    // Log Exit
    std::cout << application_name << " : Exiting" << std::endl;

    return 0;
}

