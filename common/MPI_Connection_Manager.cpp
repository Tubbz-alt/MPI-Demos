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
 * Constructor
*/
MPI_Connection::MPI_Connection()
{
}

/**
 * MPI Connection
 */
MPI_Connection::MPI_Connection(  std::string const& system_name,
                                 MPI_Comm const& comm)
  :  m_system_name(system_name),
     m_class_name("MPI_Connection"),
     m_inter_communicator(comm)
{
    MPI_Intercomm_merge( m_inter_communicator, true, &m_intra_communicator );

    MPI_Comm_size(m_intra_communicator, &m_comm_size);
    MPI_Comm_rank(m_intra_communicator, &m_comm_rank);

    int flag1, flag2;
    MPI_Comm_test_inter( m_inter_communicator, &flag1);
    MPI_Comm_test_inter( m_intra_communicator, &flag2);
    
}

/**
 * Disconnect
*/
void MPI_Connection::Disconnect()
{
    MPI_Comm_disconnect(&m_inter_communicator);
}

/**
 * Send Message
*/
void MPI_Connection::Send_Message( const std::string& message, const int& rank )
{
    MPI_Send( message.c_str(), message.size(), MPI_CHAR, rank, 0, m_intra_communicator);
}


/**
 * Receive Message
*/
std::string MPI_Connection::Recv_Message( ){

    // Get message size
    int incoming_msg_size;
    MPI_Status status;
    MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, m_intra_communicator, &status);
    MPI_Get_count(&status, MPI_BYTE, &incoming_msg_size);

    // Receive Message
    char* buffer = new char[incoming_msg_size];
    MPI_Recv( buffer,incoming_msg_size, MPI_CHAR, status.MPI_SOURCE, status.MPI_TAG, m_intra_communicator, &status );

    // Set buffer
    std::string output = buffer;

    // Delete buffer
    delete [] buffer;

    // return data
    return output;
}

/**
 * Constructor
 */
MPI_Connection_Manager::MPI_Connection_Manager( const std::string& system_name )
  : m_system_name(system_name)
{
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

    if( mpi_thread_required != m_mpi_thread_provided )
    {
        std::cerr << "warning: MPI_Init_thread requested " << mpi_thread_required << " but got " << m_mpi_thread_provided << std::endl;
    }

}

/**
 * Synchronize with a remote MPI
 */
MPI_Connection MPI_Connection_Manager::Connect_Remote( const std::string& system_name,
                                                       const std::string& hostname,
                                                       const int& port)
{
    // Create a socket
    Socket connection = Socket::Connect( hostname, port );
    
    // Read the port
    std::string mpi_port = connection.Read();

    // Connect
    MPI_Comm intercomm;
    MPI_Comm_connect( mpi_port.c_str(), MPI_INFO_NULL, 0, MPI_COMM_WORLD, &intercomm );

    // Close the connection
    connection.Close();

    // Return 
    return MPI_Connection( system_name, intercomm );
}


/**
 * Synchronize with a remote MPI
*/
MPI_Connection MPI_Connection_Manager::Connect_Client( const std::string& system_name, 
                                                       const int& port )
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
    MPI_Comm_accept( mpi_port, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &intercomm);

    // Close the Port
    MPI_Close_port( mpi_port );

    // Close the connection
    connection.Close();

    return MPI_Connection( system_name, intercomm );
}


/**
 * Finalize
 */
void MPI_Connection_Manager::Finalize()
{
    
    // Finalize MPI
    MPI_Finalize();
}

