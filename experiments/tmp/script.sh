#!/bin/bash
set -x
if [[ $1 == "lib" ]]; then
    echo "build lib & bin"
    cd ../
    make reference/libXKCP.so
    cd experiments
else
    echo "build bin"
fi

g++ -I ../bin/reference/libXKCP.so.headers/ sha-3.cpp -L../bin/reference/ -lXKCP -Wl,-rpath,../bin/reference/