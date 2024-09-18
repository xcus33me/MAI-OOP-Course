#!/bin/bash

if [ ! -d "build "]; then
    mkdir build
fi

cd build

cmake ..

cmake --build .

if [ -f "./runTests"]; then
    ./Debug/runTests.exe
else
    echo "No runTests file was found!"
fi