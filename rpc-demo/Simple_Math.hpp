/**
 * @file    Simple_Math.hpp
 * @author  Marvin Smith
 * @date    4/18/2015
 */
#ifndef __MPI_DEMOS_RPC_DEMO_SIMPLE_MATH_HPP__
#define __MPI_DEMOS_RPC_DEMO_SIMPLE_MATH_HPP__

namespace MATH{
namespace SIMPLE{

/**
 * @brief Add two numbers
 */
template <typename TP>
TP Add( TP const& value01, TP const& value02 )
{
    return (value01 + value02);
}

} // End of SIMPLE Namespace
} // End of MATH   Namespace

#endif
