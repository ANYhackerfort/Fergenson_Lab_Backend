#!/bin/bash

# Create libs directory
mkdir -p libs

# Download and extract LibTorch
echo "Downloading LibTorch..."
wget https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-latest.zip -O libs/libtorch.zip
unzip libs/libtorch.zip -d libs
mv libs/libtorch libs/pytorch  # Ensure correct directory name

# Download and extract Boost
echo "Downloading Boost..."
wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz -O libs/boost.tar.gz
mkdir -p libs/boost
tar -xvf libs/boost.tar.gz -C libs/boost --strip-components=1  # Flatten structure

# Download and build OpenCV
echo "Cloning OpenCV..."
git clone https://github.com/opencv/opencv.git libs/opencv
cd libs/opencv
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)  # Build using all available processors
cd ../../../