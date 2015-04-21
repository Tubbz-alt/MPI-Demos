/**
 * @file    MPI_RPC_Message_Builder.cpp
 * @author  Marvin Smith
 * @date    4/20/2015
*/
#include "MPI_RPC_Message_Builder.hpp"

// C++ Standard Libraries
#include <iostream>
#include <string>

// Boost Serializable
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

/**
 * @class Message_Components
 */
class Message_Components{

    public:
        
        /**
         * @brief Serialize the Component Structure.
         */
        template<class Archive>
        void serialize(Archive &ar, const unsigned int version)
        {
            // save/load base class information
            ar & method_name & arguments;
        }

        
        /// Method Name
        std::string method_name;

        /// Arguments
        MPI_RPC_Arguments arguments;

}; // End of Message_Components


/**
 * Constructor
 */
MPI_RPC_Message_Builder::MPI_RPC_Message_Builder( const std::string&        method_name,
                                                  MPI_RPC_Arguments const&  arguments )
  : m_method_name(method_name),
    m_arguments(arguments)
{

    // Arguments
    Message_Components components;
    components.method_name = method_name;
    components.arguments   = arguments;

    // Convert
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);

    oa << components;

    // don't forget to flush the stream to finish writing into the buffer
    s.flush();

    // now you get to const char* with serial_str.data()
    m_buffer = serial_str.data();
    m_buffer_size_bytes = serial_str.size(); 
}

/**
 * Set the buffer size
*/
void MPI_RPC_Message_Builder::Set_Buffer_Data( const char* buffer,
                                               const int&  buffer_size_bytes )
{
    // Message Components
    Message_Components components;

    // wrap buffer inside a stream and deserialize serial_str into obj
    boost::iostreams::basic_array_source<char> device( buffer, buffer_size_bytes );
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);
    boost::archive::binary_iarchive ia(s);
    ia >> components;

    // Copy to buffer
    m_buffer_size_bytes = buffer_size_bytes;

}


