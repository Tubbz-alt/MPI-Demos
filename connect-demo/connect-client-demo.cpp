/**
 * @file    connect-client-demo.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

// MPI Libraries
#include <mpi.h>

// Demo Libraries
#include <common/MPI_Connection_Manager.hpp>
#include <common/Socket.hpp>

using namespace std;


// Application Name
const std::string application_name = "connect-client-demo";


/**
 * @brief Main Function
 */
int main( int argc, char* argv[] )
{
    
    // Print Entry
    std::cout << application_name << " : Starting" << std::endl;

    // Create the Connection Manager
    MPI_Connection_Manager::ptr_t connection_manager(new MPI_Connection_Manager(application_name));

    // Initialize
    connection_manager->Initialize( argc, argv );

    // Connect with the remote server
    MPI_Connection remote_connection;
    remote_connection = connection_manager->Connect_Remote(application_name,"localhost", 1234);
    
    // Wait for initial reponse
    std::string msg = remote_connection.Recv_Message();
    std::cout << application_name << " : Received Message: " << msg << std::endl;
    
    // Disconnect
    remote_connection.Disconnect();
    
    // Finalize
    connection_manager->Finalize();

    // Log Exit
    std::cout << application_name << " : Exiting" << std::endl;

    return 0;

}

