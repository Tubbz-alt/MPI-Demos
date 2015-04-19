/**
 * @file    MPI_Connection_Manager.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
*/
#include "MPI_Connection_Manager.hpp"

// Local Libraries
#include "Socket.hpp"

// MPI Libraries
#include <mpi.h>

// C++ Standard Libraries
#include <iostream>


/**
 * MPI Connection
 */
MPI_Connection::MPI_Connection()
  : m_communicator(MPI_COMM_WORLD)
{

}

/**
 * MPI Connection
 */
MPI_Connection::MPI_Connection(MPI_Comm const& comm)
  : m_communicator(comm)
{

}

/**
 * Disconnect
*/
void MPI_Connection::Disconnect()
{
    MPI_Comm_disconnect(&m_communicator);
}

/**
 * Send Message
*/
void MPI_Connection::Send_Message( const std::string& message, const int& rank )
{
    MPI_Send( message.c_str(), message.size(), MPI_CHAR, rank, 0, m_communicator);
}


/**
 * Receive Message
*/
std::string MPI_Connection::Recv_Message( ){

    // Get message size
    int incoming_msg_size;
    MPI_Status status;
    MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_BYTE, &incoming_msg_size);
    
    // Receive Message
    char* buffer = new char[incoming_msg_size];
    MPI_Recv( buffer,incoming_msg_size, MPI_CHAR, status.MPI_SOURCE, status.MPI_TAG, m_communicator, &status );

    // Set buffer
    std::string output = buffer;
    std::cout << "TEMP: " << buffer << std::endl;

    // Delete buffer
    delete [] buffer;

    // return data
    return output;
}

/**
 * Initialize
 */
void MPI_Connection_Manager::Initialize( int argc, char* argv[] )
{
    // Initialize MPI
    int mpi_thread_required = MPI_THREAD_MULTIPLE;
    MPI_Init_thread( &argc, 
                     &argv, 
                     mpi_thread_required, 
                     &m_mpi_thread_provided );



}

/**
 * Synchronize with a remote MPI
 */
MPI_Connection MPI_Connection_Manager::Connect_Remote( const std::string& hostname,
                                                       const int& port)
{
    // Create a socket
    Socket connection = Socket::Connect( hostname, port );
    
    // Read the port
    std::string mpi_port = connection.Read();

    // Connect
    MPI_Comm intercomm;
    MPI_Comm_connect( mpi_port.c_str(), MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm );

    // Return 
    return MPI_Connection( intercomm );
}


/**
 * Synchronize with a remote MPI
*/
MPI_Connection MPI_Connection_Manager::Connect_Client( const int& port )
{
    // Create a socket
    Socket connection = Socket::Listen( port );

    // Get the port
    char mpi_port[MPI_MAX_PORT_NAME];
    MPI_Open_port( MPI_INFO_NULL, mpi_port );

    // Send to client
    connection.Write(std::string(mpi_port));

    // Return connection
    MPI_Comm intercomm;
    MPI_Comm_accept( mpi_port, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);

    return MPI_Connection( intercomm );
}


/**
 * Finalize
 */
void MPI_Connection_Manager::Finalize()
{
    
    // Finalize MPI
    MPI_Finalize();
}

