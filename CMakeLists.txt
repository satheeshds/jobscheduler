cmake_minimum_required(VERSION 3.10)

# Set the project name in a variable
set(PROJECT_NAME JobHeap)
# set(CLANG_TIDY_CHECKS "-checks=-*,modernize-*,readability-*,performance-*,clang-analyzer-*,cppcoreguidelines-*,concurrency-*,misc-*,bugprone-*,google-*,hicpp-*")
project(${PROJECT_NAME})

message(STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
        croncpp
        GIT_REPOSITORY https://github.com/mariusbancila/croncpp.git
        GIT_TAG        v2023.03.30
        )
FetchContent_MakeAvailable(croncpp)

add_subdirectory(lib)

add_subdirectory(examples)

add_subdirectory(tests)

add_custom_target(tidy
        DEPENDS tidy_lib tidy_examples
        COMMENT "Running clang-tidy"
        )
