/**
 * @file    rpc-server.cpp
 * @author  Marvin Smith
 * @date    4/17/2015
*/

// C++ Standard Libraries
#include <iostream>

using namespace std;

int main( int argc, char* argv[] )
{

    // Create the MPI RPC Server
    MPI_RPC_Server::ptr_t server = MPI_RPC_Server::Initialize(argc, argv);

    return 0;
}

