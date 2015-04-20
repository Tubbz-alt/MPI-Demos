/**
 * @file    MPI_RPC_Arguments.hpp
 * @author  Marvin Smith
 * @date    4/19/2015
*/
#ifndef __MPI_RPC_ARGUMENTS_HPP__
#define __MPI_RPC_ARGUMENTS_HPP__

// C++ Standard Libraries
#include <vector>

/**
 * @class MPI_RPC_Arguments
*/
class MPI_RPC_Arguments{

    public:
        
        /**
         * Push argument into argument list
        */
        template <typename TP>
        void push_back( TP const& arg )
        {
            const char* buffer_data = reinterpret_cast<const char*>(&arg);
            for( int i=0; i<sizeof(TP); i++ ){
                m_buffer_data.push_back(buffer_data[i]);
            }
        }


    private:
        
        /// Buffer Information
        std::vector<char> m_buffer_data;

}; // End of MPI_RPC_Arguments Class

#endif
