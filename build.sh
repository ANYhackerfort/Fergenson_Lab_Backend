#!/bin/bash

# Create and navigate to the build directory
rm -rf build
mkdir -p build
cd build

# cmake -DCMAKE_PREFIX_PATH=/Users/matthewzhang/websocket-Fergenson/libs/libtorch ..

# Run CMake and Make
cmake ..
make

# Execute the output file (replace 'output_file_name' with your target's name)
./WebSocketWithOpenCV
