#!/bin/bash
cd ..
if [[ -d "build" ]]
then
    rm -rf build
fi
mkdir build && cd build
directory=`pwd`
cmake .. -DOnePass_BUILD_EXECUTABLE=1 -DCMAKE_INSTALL_PREFIX=${directory}
cmake --build . --target install
./bin/OnePass
ctest -C Release