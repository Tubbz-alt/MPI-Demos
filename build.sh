#!/bin/sh

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
make 
if [ ! "$?" = '0' ]; then
    echo 'error with Make. Aborting.'
    exit 1
fi


#  Exit Release
popd

