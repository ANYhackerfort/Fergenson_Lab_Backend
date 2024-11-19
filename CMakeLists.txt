cmake_minimum_required(VERSION 3.10)
project(WebSocketWithOpenCV)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for your project headers
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/websocket_f)
include_directories(${PROJECT_SOURCE_DIR}/include/openCV_f)

# Find dependencies for Open_AI Library
find_package(nlohmann_json CONFIG REQUIRED)
find_package(curl REQUIRED)

# Find Boost using imported targets
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV REQUIRED)

# Find and include OpenCV
find_package(OpenCV REQUIRED)

# Add source files
set(SOURCES
    src/websocket_s/websocket_server.cpp
    src/openCV_s/process_image.cpp
)

# Add executable target
add_executable(WebSocketWithOpenCV ${SOURCES})

# Find the Open_Ai Library
if(DEFINED OPENAI_DIR)
    find_library(OPENAI_LIB oai PATHS ${OPENAI_DIR}/build)
    include_directories(${OPENAI_DIR}/include)
    target_link_libraries(WebSocketWithOpenCV PRIVATE CURL::libcurl)
    target_link_libraries(WebSocketWithOpenCV PRIVATE nlohmann_json::nlohmann_json)
    target_link_libraries(WebSocketWithOpenCV PRIVATE ${OPENAI_LIB})
endif()

# Link libraries (Boost and OpenCV)
target_link_libraries(WebSocketWithOpenCV PRIVATE Boost::system ${OpenCV_LIBS})