#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/19/2015
#
#    Purpose:    Build the MPI RPC Demo
#

#  Add the Spawn Demo Sources
set( MPI_RPC_DEMO_SOURCES
    MPI_RPC_Address_Table.cpp
    MPI_RPC_Server.cpp
)


#  Add the Spawn Demo Headers
set( MPI_RPC_DEMO_HEADERS
    MPI_RPC_Address_Table.hpp
    MPI_RPC_Arguments.hpp
    MPI_RPC_Server.hpp
    MPI_RPC_Results.hpp
)


#------------------------------------------#
#-      Create the Main Executables       -#
#------------------------------------------#
add_executable( rpc-demo
                rpc-demo.cpp
                ${MPI_RPC_DEMO_SOURCES}
                ${MPI_RPC_DEMO_HEADERS}
)
add_executable( rpc-server
                rpc-server.cpp
                ${MPI_RPC_DEMO_SOURCES}
                ${MPI_RPC_DEMO_HEADERS}
)

#-----------------------------#
#-      Link Libraries       -#
#-----------------------------#
target_link_libraries( rpc-demo
                       ${MPI_LIBRARIES}
)

target_link_libraries( rpc-server
                       ${MPI_LIBRARIES}
)



