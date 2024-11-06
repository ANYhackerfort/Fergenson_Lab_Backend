# WebSocketWithOpenCV Project

This project is a WebSocket server that uses Boost, OpenCV, and C++ to perform image processing. The server processes images, detects edges, and sends a confirmation message to the client upon completion. The project includes support for displaying processed images on the backend and can be configured to save output images instead.

## Prerequisites

Before setting up this project, ensure that the following libraries and tools are installed on your system:

- **CMake** (version 3.10 or higher)
- **Boost** (including Boost.Asio and Boost.Beast)
- **OpenCV** (version 4.0 or higher)
- **A C++ Compiler** (supporting C++17 or higher)

## Installation

1. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd WebSocketWithOpenCV

2. **Make Build Directory**
mkdir build
cd build

3. **Change MakeList to update where your files are**
I recommend you to have a libs folder that includes the cloned version of boost and openCV.

4. **CMake**
cmake ..

5. **Make**
make





