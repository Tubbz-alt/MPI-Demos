#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    4/17/2015
#
#    Purpose:    Build the MPI Spawn Demo
#

#  Add the Spawn Demo Sources
set( SPAWN_DEMO_SOURCES
    src/Spawn_Demo_Common.cpp
)


#  Add the Spawn Demo Headers
set( SPAWN_DEMO_HEADERS
    src/Spawn_Demo_Common.hpp
)


#------------------------------------------#
#-      Create the Main Executables       -#
#------------------------------------------#
add_executable( spawn-demo
                src/spawn-demo.cpp
                ${SPAWN_DEMO_SOURCES}
                ${SPAWN_DEMO_HEADERS}
)
add_executable( child-persistent
                src/child-persistent.cpp
                ${SPAWN_DEMO_SOURCES}
                ${SPAWN_DEMO_HEADERS}
)
add_executable( child-temporary
                src/child-temporary.cpp
                ${SPAWN_DEMO_SOURCES}
                ${SPAWN_DEMO_HEADERS}
)
add_executable( child-segfault
                src/child-segfault.cpp
                ${SPAWN_DEMO_SOURCES}
                ${SPAWN_DEMO_HEADERS}
)

#-----------------------------#
#-      Link Libraries       -#
#-----------------------------#
target_link_libraries( spawn-demo
                       ${MPI_LIBRARIES}
)

target_link_libraries( child-persistent
                       ${MPI_LIBRARIES}
)

target_link_libraries( child-temporary
                       ${MPI_LIBRARIES}
)

target_link_libraries( child-segfault
                       ${MPI_LIBRARIES}
)

