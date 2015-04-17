/**
 * @file    String_Utilities.hpp
 * @author  Marvin Smith
 * @date    4/17/2015
 */
#ifndef __MPI_DEMOS_COMMON_STRING_UTILITIES_HPP__
#define __MPI_DEMOS_COMMON_STRING_UTILITIES_HPP__

// C++ Standard Libraries
#include <sstream>
#include <string>


/**
 * @brief Convert a string to number
 */
template <typename TP>
TP str2num( std::string const& str )
{
    std::stringstream sin;
    sin << str;
    TP output;
    sin >> output;
    return output;
}


#endif
