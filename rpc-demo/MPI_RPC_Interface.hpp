/**
 * @file    MPI_RPC_Interface.hpp
 * @author  Marvin Smith
 * @date    4/19/2015
*/
#ifndef __MPI_RPC_INTERFACE_HPP__
#define __MPI_RPC_INTERFACE_HPP__

#include "MPI_RPC_Server.hpp"

namespace MPI_RPC{
namespace MATH{
namespace SIMPLE{

/**
 * @brief Add Two Numbers
*/
template <typename TP>
TP Add( TP const& value1, TP const& value2 )
{
    // Create an argument list
    MPI_RPC_Arguments arguments;
    arguments.push_back(value1);
    arguments.push_back(value2);

    // Create a result object
    MPI_RPC_Results results;

    // Execute the command
    MPI_RPC_Host::Execute_Command("MATH::SIMPLE::Add", arguments, results );

    // Return the results
    return results.Get<TP>();
}


} // End of SIMPLE Namespace
} // End of MATH Namespace
} // End of MPI_RPC Namespace

#endif
