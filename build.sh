#!/bin/bash

# Create and navigate to the build directory
mkdir -p build
cd build

# Run CMake and Make
cmake ..
make

# Execute the output file (replace 'output_file_name' with your target's name)
./WebSocketWithOpenCV
