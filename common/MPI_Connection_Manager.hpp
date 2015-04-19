/**
 * @file    MPI_Connection_Manager.hpp
 * @author  Marvin Smith
 * @date    4/18/2015
*/
#ifndef __MPI_DEMOS_CONNECT_COMMON_MPI_CONNECTION_MANAGER_HPP__
#define __MPI_DEMOS_CONNECT_COMMON_MPI_CONNECTION_MANAGER_HPP__

// C++ Standard Libraries
#include <memory>

// MPI Libraries
#include<mpi.h>

/**
 * @class MPI_Connection
 */
class MPI_Connection{

    public:
        
        /**
         * @brief Constructor
         */
        MPI_Connection();


        /**
         * @brief Constructor
         */
        MPI_Connection( MPI_Comm const& comm );


        /**
         * @brief Disconnect
        */
        void Disconnect();


        /**
         * @brief Send Message
        */
        void Send_Message( const std::string& message, const int& rank );

        /**
         * @brief Receive Message
         */
        std::string Recv_Message();


    private:
        
        /// MPI Communicator
        MPI_Comm m_communicator;

}; // End of MPI_Connection Class

/**
 * @class MPI_Connection_Manager
 *
 * @brief Stores various connection information for MPI and Sockets.
 */
class MPI_Connection_Manager{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<MPI_Connection_Manager> ptr_t;


        /**
         * @brief Initialize
         */
        void Initialize( int argc, char* argv[] );


        /**
         * @brief Finalize
         */
        void Finalize();


        /**
         * @brief Connect with remote Client.
         */
        MPI_Connection Connect_Remote( const std::string& hostname,
                                       const int& port );


        /**
         * @brief Connect with a remote server.
         */
        MPI_Connection Connect_Client( const int& port );


    private:
        
        /// MPI Thread Type
        int m_mpi_thread_provided;


}; // End of Connection_Manager Class


#endif
