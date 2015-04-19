#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/17/2015
#
#    Purpose:  Build the Connection Demo.
#


#-----------------------------------#
#-      Create the Executable      -#
#-----------------------------------#
add_executable( connect-client-demo
                connect-client-demo.cpp
)
add_executable( connect-server-demo
                connect-server-demo.cpp
)

target_link_libraries( connect-server-demo
                       ${MPI_LIBRARIES}
                       MPI_Demo_Common
)

target_link_libraries( connect-client-demo
                       ${MPI_LIBRARIES}
                       MPI_Demo_Common
)

