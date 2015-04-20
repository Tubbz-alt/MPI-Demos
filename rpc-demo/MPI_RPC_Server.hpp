/**
 * @file    MPI_RPC_Server.hpp
 * @author  Marvin Smith
 * @date    4/17/2015
*/
#ifndef __MPI_DEMOS_RPC_DEMO_MPI_RPC_SERVER_HPP__
#define __MPI_DEMOS_RPC_DEMO_MPI_RPC_SERVER_HPP__

// MPI RPC Libraries
#include "MPI_RPC_Address_Table.hpp"
#include "MPI_RPC_Arguments.hpp"
#include "MPI_RPC_Results.hpp"

/**
 * @class MPI_RPC_Server
*/
class MPI_RPC_Server{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<MPI_RPC_Server> ptr_t;


        /**
         * @brief Initialize the RPC Server.
         *
         * @param[in] argc Number of arguments.
         * @param[in] argv List of arguments.
         */
        MPI_RPC_Server::ptr_t  Initialize( int argc, char* argv[] );


}; // End of MPI_RPC_Server Class


/**
 * @class MPI_RPC_Host
*/
class MPI_RPC_Host{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<MPI_RPC_Host> ptr_t;

        /**
         * @brief Constructor
         */
        MPI_RPC_Host();
        
        /**
         * @brief Execute an RPC Command
         */
        static void Execute_Command( const std::string& method_name, 
                                     const MPI_RPC_Arguments& arguments,
                                     MPI_RPC_Results& results );
        
        /**
         * @brief Initialize
         */
        static void Initialize( int argc, char* argv[] );


    private:
        
        /// MPI Address Table
        MPI_RPC_Address_Table::ptr_t m_address_table;

}; // End of MPI_RPC_Host Class


#endif
