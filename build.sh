#!/bin/sh

# Important Global Variables
NUM_THREADS=1


#-------------------------------#
#-             Usage           -#
#-------------------------------#
Usage(){

    echo "usage: $0 <flags>"
    echo ''
    echo '-h | --help    : Print usage instructions.'
    echo '-m             : Build software.'
    echo '-c             : Clean software.'
    echo ''
    exit 1
}

#-------------------------------#
#-     Clean up software       -#
#-------------------------------#
clean_software(){
    
    #  Log Entry
    echo '-> Cleaning Software'

    #  Delete repo
    rm -r release

}

#-------------------------------#
#-     Construct MPI Demos     -#
#-------------------------------#
build_software(){

    #  Log Entry
    echo '-> Building Software' 

    #  Create Release Directory
    mkdir -p release

    #  Enter Release Directory
    pushd release

    #  Run Cmake
    cmake ..
    if [ ! "$?" = '0' ]; then
        echo 'error with CMake. Aborting.'
        exit 1
    fi

    #  Run Make
    make -j$NUM_THREADS
    if [ ! "$?" = '0' ]; then
        echo 'error with Make. Aborting.'
        exit 1
    fi


    #  Exit Release
    popd
}


#---------------------------------------------#
#-       Process Command-Line Arguments      -#
#---------------------------------------------#

#  State Flags
RUN_MAKE=1
RUN_CLEAN=0
SET_THREADS=0

#  Iterate
for ARG in "$@"; do
    case $ARG in
        
        #  Print Usage Instructions
        '-h')
            Usage
            ;;

        #  Build Software
        '-m')
            RUN_MAKE=1
            ;;

        #  Clean Software
        '-c')
            RUN_CLEAN=1
            RUN_MAKE=0
            ;;

        #  Set threads
        '-j')
            SET_THREADS=1
            ;;

        #  Otherwise there is an arg to parse or error
        *)

            #  Set threads
            if [ "$SET_THREADS" = '1' ]; then
                NUM_THREADS=$ARG
                SET_THREADS=0
            
            # Process the parsing error
            else
                echo "error: Unable to parse argument ($ARG)"
                Usage
            fi
            ;;
    esac
done


#  Clean Software
if [ "$RUN_CLEAN" = '1' ]; then
    clean_software
fi

#  Build Software
if [ "$RUN_MAKE" = '1' ]; then
    build_software
fi


