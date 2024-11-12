cmake_minimum_required(VERSION 3.10)
project(WebSocketWithOpenCV)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for your project headers
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/websocket_f)
include_directories(${PROJECT_SOURCE_DIR}/include/openCV_f)

# Manually include directories for Tesseract and Leptonica headers
include_directories(${PROJECT_SOURCE_DIR}/libs/tesseract)
include_directories(${PROJECT_SOURCE_DIR}/libs/leptonica)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
else()
    message(FATAL_ERROR "Boost not found.")
endif()

# Find OpenCV
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "OpenCV found: ${OpenCV_VERSION}")
else()
    message(FATAL_ERROR "OpenCV not found.")
endif()

# Find Tesseract and Leptonica Libraries
set(Tesseract_LIBRARIES "${PROJECT_SOURCE_DIR}/libs/tesseract/tesseract/lib/libtesseract.dylib")  # Update path if needed
set(Leptonica_LIBRARIES "${PROJECT_SOURCE_DIR}/libs/leptonica/leptonica/lib/libleptonica.dylib")  # Update path if needed

# Add source files
set(SOURCES
    src/websocket_s/websocket_server.cpp
    src/openCV_s/process_image.cpp
)

# Add executable target
add_executable(WebSocketWithOpenCV ${SOURCES})

# Link libraries (Boost, OpenCV, Tesseract, and Leptonica)
target_link_libraries(WebSocketWithOpenCV 
    Boost::system 
    ${OpenCV_LIBS} 
    ${Tesseract_LIBRARIES} 
    ${Leptonica_LIBRARIES}
)
