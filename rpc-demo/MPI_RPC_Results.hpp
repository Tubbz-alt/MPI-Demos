/**
 * @file    MPI_RPC_Results.hpp
 * @author  Marvin Smith
 * @date    4/17/2015
*/
#ifndef __MPI_RPC_RESULTS_HPP__
#define __MPI_RPC_RESULTS_HPP__

// C++ Standard Libraries
#include <memory>

/**
 * @class MPI_RPC_Results
*/
class MPI_RPC_Results{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<MPI_RPC_Results> ptr_t;

        /**
         * Get item
        */
        template <typename TP>
        TP Get( )const{
            return 0;
        }


}; // End of MPI_RPC_Results

#endif
