/**
 * @file    connect-server-demo.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */

// C++ Standard Libraries
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

// Demo Libraries
#include <common/MPI_Connection_Manager.hpp>
#include <common/Socket.hpp>

// MPI Libraries
#include <mpi.h>

using namespace std;

// Application Name
std::string application_name = "connect-server-demo";


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
        
    // Connect with client
    MPI_Connection remote_connection = connection_manager->Connect_Client(application_name, 1234);

    // Send a message
    std::cout << application_name << " : Sending Message" << std::endl;
    remote_connection.Send_Message("Connection Established", 1);

    // Disconnect
    remote_connection.Disconnect();

    // Finalize
    connection_manager->Finalize();

    // Log Exit
    std::cout << application_name << " : Exiting" << std::endl;

    return 0;
}

