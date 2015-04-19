#    File:     CMakeLists.txt
#    Author:   Marvin Smith
#    Date:     4/17/2015
#
#    Purpose Build the Common API
#

#---------------------------------------#
#-      Define our Common Sources      -#
#---------------------------------------#
set( COMMON_SOURCES
     MPI_Connection_Manager.cpp
     Socket.cpp
)

#---------------------------------------#
#-      Define our Common Headers      -#
#---------------------------------------#
set( COMMON_HEADERS
     MPI_Connection_Manager.hpp
     Socket.hpp
)


#--------------------------------#
#-      Create the Library      -#
#--------------------------------#
add_library( MPI_Demo_Common  STATIC
                ${COMMON_SOURCES}
                ${COMMON_HEADERS}
)

