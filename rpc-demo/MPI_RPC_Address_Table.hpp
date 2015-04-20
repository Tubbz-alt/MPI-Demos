/**
 * @file    MPI_RPC_Address_Table.hpp
 * @author  Marvin Smith
 * @date    4/17/2015
*/
#ifndef __MPI_RPC_ADDRESS_TABLE_HPP__
#define __MPI_RPC_ADDRESS_TABLE_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>
#include <vector>

// RPC Libraries
#include <common/MPI_Connection_Manager.hpp>

/**
 * @class MPI_RPC_Address_Table
 */
class MPI_RPC_Address_Table{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<MPI_RPC_Address_Table> ptr_t;

        /**
         * @brief Check contents
         */
        bool Find_Connection( const std::string& method_name, 
                              MPI_Connection::ptr_t& connection,
                              int& rank );
        

    private:
        
        /// List of Connections 
        std::vector<MPI_Connection::ptr_t> m_connections;

        /// List of Method Names
        std::vector<std::vector<std::string>> m_method_names;

}; // End of MPI_RPC_Address_Table

#endif
