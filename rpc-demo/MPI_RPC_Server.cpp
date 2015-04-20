/**
 * @file    MPI_RPC_Server.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
*/
#include "MPI_RPC_Server.hpp"

// C++ Standard Libraries
#include <cstdlib>
#include <iostream>

// RPC Host Instance
MPI_RPC_Host::ptr_t host_instance(nullptr);

// RPC Server Instance
MPI_RPC_Server::ptr_t server_instance(nullptr);

/**
 * Initialize the Server
 */
MPI_RPC_Server::ptr_t MPI_RPC_Server::Initialize( int argc, char* argv[] )
{

    // If null, initialize
    if( server_instance == nullptr ){
        server_instance = MPI_RPC_Server::ptr_t(new MPI_RPC_Server());
    }

    return server_instance;
}


/**
 * Constructor
*/
MPI_RPC_Host::MPI_RPC_Host()
  : m_address_table(nullptr)
{
}

/**
 * Execute Command
*/
void MPI_RPC_Host::Execute_Command( const std::string& method_name,
                                    MPI_RPC_Arguments const& arguments,
                                    MPI_RPC_Results   const& results )
{
    // Fetch the host
    MPI_RPC_Host::ptr_t host = host_instance;

    // Create the MPI Connection Pointer
    MPI_Connection::ptr_t connection;

    // Look for a Server which has the method registered
    int rank;
    if(  host->m_address_table->Find_Connection( method_name, connection, rank ) == false )
    {
        std::cerr << "Unable to find connection containing the method." << std::endl;
        std::exit(-1);
    }

    // Send the Message
    MPI_RPC_Message_Builder message( method_name, arguments, results );

    connection->Send_Message( message.Get_Buffer(), 
                              message.Get_Buffer_Size_Bytes(),
                              rank );

}

/**
 * Initialize
*/
void MPI_RPC_Host::Initialize( int argc, char* argv[] )
{
    // Create the instance
    if( host_instance == nullptr )
    {
        host_instance = MPI_RPC_Host::ptr_t(new MPI_RPC_Host());
    }
}

