/**
 * @file    Socket.hpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#ifndef __MPI_DEMO_COMMON_SOCKET_HPP__
#define __MPI_DEMO_COMMON_SOCKET_HPP__

// C++ Standard Libraries
#include <string>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

/**
 * @class Socket
*/
class Socket{
    
    public:

        /**
         * @brief Constructor
         */
        Socket();


        /**
         * @brief Constructor
        */
        Socket( const int& socket_fd );
        

        /**
         * @brief Close the socket.
        */
        void Close();
        
        /**
         * @brief Read from the socket
         */
        std::string Read();


        /**
         * @brief Write to the socket.
        */
        void Write( const std::string& message );


        /**
         * @brief Listen for Connections
         */
         static Socket Listen( const int& port_number );
        
        /**
         * @brief Connect to the Server
        */
        static Socket Connect( const std::string& hostname,
                               const int& port );

    private:
        
        // Server Socket File Descriptor
        int m_sock_fd;


}; // End of Socket Class

#endif
