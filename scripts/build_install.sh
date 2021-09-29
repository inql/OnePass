#!/bin/bash
cd ..
if [[ -d "build" ]]
then
    rm -rf build
fi
mkdir build && cd build
directory=`pwd`
cmake .. -DCMAKE_INSTALL_PREFIX=${directory}
cmake --build . --target install
./bin/OnePass