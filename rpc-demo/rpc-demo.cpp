/**
 * @file    rpc-demo.cpp
 * @author  Marvin Smith
 * @date    4/19/2015
*/

// C++ Standard Libraries
#include <iostream>

// MPI RPC Interfaces
#include "MPI_RPC_Interface.hpp"

using namespace std;

int main( int argc, char* argv[] )
{

    // Initialize the MPI RPC Server
    MPI_RPC_Host::Initialize(argc, argv);

    // Call on the simple math API
    int result = MPI_RPC::MATH::SIMPLE::Add( 4, 3 );
    std::cout << "Result: " << result << std::endl;

    return 0;
}

