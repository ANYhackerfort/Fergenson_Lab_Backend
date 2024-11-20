cmake_minimum_required(VERSION 3.10)
project(WebSocketWithOpenCV)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for your project headers
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/websocket_f)
include_directories(${PROJECT_SOURCE_DIR}/include/openCV_f)

# Find Directories, accounts for if you have an environment where cmake can find it automatically. 

if (NOT Torch_DIR)
    set(Torch_DIR "${CMAKE_SOURCE_DIR}/libs/libtorch/share/cmake/Torch" CACHE PATH "Path to Torch library")
    message(STATUS "Torch_DIR not provided. Using default: ${Torch_DIR}")
else()
    message(STATUS "Using user-provided Torch_DIR: ${Torch_DIR}")
endif()

if (NOT OpenCV_DIR)
    set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/libs/opencv/lib/cmake/opencv4" CACHE PATH "Path to OpenCV library")
    message(STATUS "OpenCV_DIR not provided. Using default: ${OpenCV_DIR}")
else()
    message(STATUS "Using user-provided OpenCV_DIR: ${OpenCV_DIR}")
endif()

if (NOT Boost_DIR)
    set(Boost_DIR "${CMAKE_SOURCE_DIR}/libs/boost" CACHE PATH "Path to Boost library")
    message(STATUS "Boost_DIR not provided. Using default: ${Boost_DIR}")
else()
    message(STATUS "Using user-provided Boost_DIR: ${Boost_DIR}")
endif()

if (NOT EXISTS "${Torch_DIR}")
    message(FATAL_ERROR "Torch directory structure not set up right or you didn't clone all dependencies. Expected: ${Torch_DIR}")
endif()
if (NOT EXISTS "${Boost_DIR}")
    message(FATAL_ERROR "Boost directory structure not set up right or you didn't clone all dependencies. Expected: ${Boost_DIR}")
endif()
if (NOT EXISTS "${OpenCV_DIR}/OpenCVConfig.cmake")
    message(FATAL_ERROR "OpenCV directory structure not set up right or you didn't clone all dependencies. Expected: ${OpenCV_DIR}/OpenCVConfig.cmake")
endif()

# Find Packages
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)

# Find Torch
find_package(Torch REQUIRED)

# Add source files
set(SOURCES
    src/websocket_s/websocket_server.cpp
    src/openCV_s/process_image.cpp
)

# Add executable target
add_executable(WebSocketWithOpenCV ${SOURCES})

# Link libraries (Boost, OpenCV, and Torch)
target_link_libraries(WebSocketWithOpenCV
    Boost::system
    ${OpenCV_LIBS}
    ${TORCH_LIBRARIES}
)

# Add Torch include directories
target_include_directories(WebSocketWithOpenCV PRIVATE ${TORCH_INCLUDE_DIRS})

# Set C++ flags for Torch
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Ensure C++17 is used for compatibility
set_property(TARGET WebSocketWithOpenCV PROPERTY CXX_STANDARD 17)
