#!/bin/bash
cd ..
if [[ -d "build" ]]
then
    cd build
else
    mkdir build && cd build
fi
cmake .. -DOnePass_BUILD_EXECUTABLE=1 -DCMAKE_INSTALL_PREFIX=${HOME}
cmake --build . --target install
./bin/OnePass
# one by one
find bin -maxdepth 1 -name \*_Tests -exec {} \;
# overall status
ctest -C Release