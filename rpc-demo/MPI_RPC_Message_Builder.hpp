/**
 * @file    MPI_RPC_Message_Builder.hpp
 * @author  Marvin Smith
 * @date    4/20/2015
 */
#ifndef __MPI_DEMOS_MPI_RPC_MESSAGE_BUILDER_HPP__
#define __MPI_DEMOS_MPI_RPC_MESSAGE_BUILDER_HPP__

// C++ Standard Libraries
#include <string>

// RPC Libraries
#include "MPI_RPC_Arguments.hpp"

/**
 * @class MPI_RPC_Message_Builder
 */
class MPI_RPC_Message_Builder{

    public:
        
        /**
         * @brief Constructor
         */
        MPI_RPC_Message_Builder( const std::string&        method_name,
                                 const MPI_RPC_Arguments&  arguments );
        
        /**
         * @brief Get the buffer
         */
        inline const char* Get_Buffer()const{
            return m_buffer;
        }

        /**
         * @brief Get the buffer size
         */
        inline int Get_Buffer_Size_Bytes()const{
            return m_buffer_size_bytes;
        }


        /**
         * @brief Set the Buffer.
         */
        void Set_Buffer_Data( const char* buffer,
                              const int&  buffer_size_bytes );


    private:
        
        /// Method Name
        std::string m_method_name;

        /// Arguments
        MPI_RPC_Arguments m_arguments;

        /// Buffer
        const char* m_buffer;

        /// Buffer Size
        int m_buffer_size_bytes;

}; // End of MPI_RPC_Message_Builder Class

#endif
