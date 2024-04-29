cmake_minimum_required(VERSION 3.10)

# Set the project name in a variable
set(PROJECT_NAME JobHeap)
project(${PROJECT_NAME})

# Set the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
        croncpp
        GIT_REPOSITORY https://github.com/mariusbancila/croncpp.git
        GIT_TAG        v2023.03.30
        )

FetchContent_MakeAvailable(croncpp)

# Get all the .cpp files in the src directory
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# If you have other .cpp files, list them here
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${croncpp_SOURCE_DIR}/include)