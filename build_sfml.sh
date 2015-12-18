#!/bin/bash

set -e

pushd ..

# Cached version didn't work even though I followed Travis' own documentation and examples..
#Build SFML from the sources or used cached directory if it exists
#if [ ! -d "$HOME/build/ninjarope/build-sfml/lib" ]; then
    # SFML headers 
    git clone https://github.com/LaurentGomila/SFML.git sfml
    cd sfml
    git checkout tags/2.2
    cd ..

    # SFML lib
    mkdir build-sfml
    cd build-sfml
    cmake -G "Unix Makefiles" -D CMAKE_INSTALL_PREFIX=$(pwd)/install -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=TRUE ../sfml
    make
    make install
#else
    #echo 'SFML was prebuilt / using cached directory.'
#fi

popd
