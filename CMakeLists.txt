#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/17/2015
#
#    Purpose:  Build MPI Demo Programs
#


#   Set the Minimum CMake Version
cmake_minimum_required( VERSION 2.8 FATAL_ERROR )

#   Set the Project Name
project(mpi-demos)

#  Add C++11x Support
SET( CMAKE_CXX_FLAGS "-std=c++11")

#-------------------#
#-    Find MPI     -#
#-------------------#
FIND_PACKAGE( MPI REQUIRED )
include_directories( ${MPI_INCLUDE_PATH} )


#---------------------------------#
#-     Change the Output Path    -#
#---------------------------------#
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
SET( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )


#------------------------------#
#-   Include the base path    -#
#------------------------------#
include_directories(.)

#-------------------------------------#
#-     Build the Common Libraries    -#
#-------------------------------------#
add_subdirectory(common)

#---------------------#
#-      Options      -#
#---------------------#
option( BUILD_CONNECT_DEMO "Build the MPI Connection demo." ON )
option( BUILD_SPAWN_DEMO   "Build the MPI Spawn demo."      ON )
option( BUILD_RPC_DEMO     "Build the MPI RPC demo."        ON )

#----------------------------------#
#-     Build the Connect Demo     -#
#----------------------------------#
if( BUILD_CONNECT_DEMO )
    add_subdirectory(connect-demo)
endif()

#--------------------------------#
#-     Build the Spawn Demo     -#
#--------------------------------#
if( BUILD_SPAWN_DEMO )
    add_subdirectory(spawn-demo)
endif()

#------------------------------#
#-     Build the RPC Demo     -#
#------------------------------#
if( BUILD_RPC_DEMO )    
    add_subdirectory(rpc-demo)
endif()

