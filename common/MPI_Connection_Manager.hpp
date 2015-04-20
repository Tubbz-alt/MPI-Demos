/**
 * @file    MPI_Connection_Manager.hpp
 * @author  Marvin Smith
 * @date    4/18/2015
*/
#ifndef __MPI_DEMOS_CONNECT_COMMON_MPI_CONNECTION_MANAGER_HPP__
#define __MPI_DEMOS_CONNECT_COMMON_MPI_CONNECTION_MANAGER_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>

// MPI Libraries
#include<mpi.h>

/**
 * @class MPI_Connection
 */
class MPI_Connection{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<MPI_Connection> ptr_t;


        /**
         * @brief Constructor
         */
        MPI_Connection();


        /**
         * @brief Constructor
         */
        MPI_Connection( std::string const& system_name,
                        MPI_Comm const& comm );


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
        
        /// System Name
        std::string m_system_name;

        /// Class Name
        std::string m_class_name;

        /// MPI Communicator
        MPI_Comm m_inter_communicator;
        MPI_Comm m_intra_communicator;
        
        /// Comm Size
        int m_comm_size;

        /// Comm Rank
        int m_comm_rank;

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
         * @brief Constructor
         */
        MPI_Connection_Manager( const std::string& system_name );


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
        MPI_Connection Connect_Remote( const std::string& system_name,
                                       const std::string& hostname,
                                       const int& port );


        /**
         * @brief Connect with a remote server.
         */
        MPI_Connection Connect_Client( const std::string& system_name,
                                       const int& port );


    private:

        /// System Name
        std::string m_system_name;
        
        /// MPI Thread Type
        int m_mpi_thread_provided;


}; // End of Connection_Manager Class


#endif
