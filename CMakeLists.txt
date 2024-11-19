cmake_minimum_required(VERSION 3.10)
project(WebSocketWithOpenCV)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for your project headers
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/websocket_f)
include_directories(${PROJECT_SOURCE_DIR}/include/openCV_f)

# Find Boost and OpenCV
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
