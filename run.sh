#!/usr/bin/bash

if [[ -d 'build' ]]; then
    if [[ $1=='clean' ]]; then
       rm -rf build 
       mkdir build
    fi
    cd build && cmake build ..
    make
    ./astar
else
    mkdir build
    cd build && cmake build ..
    make
    ./astar
    
fi


