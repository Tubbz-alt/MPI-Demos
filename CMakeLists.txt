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
SET( CMAKE_CXX_FLAGS "-std=c++11 -rdynamic -ldl")

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


#-------------------------------------#
#-     Build the Common Libraries    -#
#-------------------------------------#
#add_subdirectory(common)

#--------------------------------#
#-     Build the Spawn Demo     -#
#--------------------------------#
add_subdirectory(spawn-demo)


