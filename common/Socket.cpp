/**
 * @file    Socket.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#include "Socket.hpp"

// C++ Standard Libraries
#include <iostream>
#include <netdb.h>
#include <unistd.h>


/**
 * Constructor
*/
Socket::Socket()
{

}


/**
 * Constructor
*/
Socket::Socket( const int& socket_fd)
  : m_sock_fd(socket_fd)
{

}

/**
 * @brief Close the socket
*/
void Socket::Close()
{
    close(m_sock_fd);
}


/**
 * Read from the socket.
*/
std::string Socket::Read()
{
    // Read
    char buffer[256];

    int len = read(m_sock_fd,buffer,255);
    if (len < 0){
        std::cerr << "error reading from socket." << std::endl;
        std::exit(-1);
    }

    std::string output = buffer;
    return output.substr(0, len);
}

/**
 * Write to Socket
*/
void Socket::Write( const std::string& message )
{
    int len = write( m_sock_fd,
                     message.c_str(),
                     message.size());
    if( len < 0 ){
        std::cerr << "error writing" << std::endl;
        std::exit(-1);
    }
}

/**
 * Listen for connections
*/
Socket Socket::Listen( const int& port_number )
{
    // Create socket fd
    int sock_fd = socket( AF_INET, SOCK_STREAM, 0 );

    if( sock_fd < 0 ){
        std::cerr << "error opening socket" << std::endl;
        std::exit(-1);
    }

    // Clear the address buffer
    sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_number);
    
    // Set socket options
    int optval;
    if( setsockopt( sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0 ){
        std::cerr << "error on setsockopt" << std::endl;
        std::exit(-1);
    }

    // Bind
    if( bind( sock_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0 ){
        std::cerr << "error on binding" << std::endl;
        std::exit(-1);
    }

    // Start listening
    listen(sock_fd,5);

    // Get the length
    sockaddr_in client_addr;
    socklen_t clilen;
    
    clilen = sizeof(client_addr);
    int client_sock_fd = accept( sock_fd, (sockaddr*)&client_addr, &clilen);


    if ( client_sock_fd < 0) {
        std::cerr << "ERROR on accept" << std::endl;
        std::exit(-1);
    }
   
    // Close the temp socket
    close(sock_fd);

    // Create output socket
    return Socket(client_sock_fd);

}

/**
 * Connect
*/
Socket Socket::Connect( const std::string& hostname,
                        const int& port )
{

    
    // Create Socket
    int sock_fd = socket( AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        std::cerr << "error opening socket." << std::endl;
        std::exit(-1);
    }


    // Get the Server Hostname
    struct hostent *server;
    server = gethostbyname(hostname.c_str());
    if (server == NULL) {
        std::cerr << "No host found." << std::endl;
        exit(-1);
    }

    // Create Server Address Container
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(  (char *)server->h_addr,  
            (char *)&serv_addr.sin_addr.s_addr,
            server->h_length);
    serv_addr.sin_port = htons(port);
    
    // Connect
    if (connect(sock_fd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        std::cerr << "ERROR connecting" << std::endl;
        std::exit(-1);
    }

    // Return socket
    return Socket(sock_fd);
}


