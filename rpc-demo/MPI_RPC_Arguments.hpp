/**
 * @file    MPI_RPC_Arguments.hpp
 * @author  Marvin Smith
 * @date    4/19/2015
*/
#ifndef __MPI_RPC_ARGUMENTS_HPP__
#define __MPI_RPC_ARGUMENTS_HPP__

// C++ Standard Libraries
#include <vector>

// Boost Serializable
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/serialization/vector.hpp>


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

        
        /**
         * @brief Serialize
         */
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            // save/load base class information
            ar & m_buffer_data;
        }

    private:
        
        /// Buffer Information
        std::vector<char> m_buffer_data;

}; // End of MPI_RPC_Arguments Class

#endif
