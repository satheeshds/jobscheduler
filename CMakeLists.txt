cmake_minimum_required(VERSION 3.10)

# Set the project name in a variable
set(PROJECT_NAME JobHeap)
# set(CLANG_TIDY_CHECKS "-checks=-*,modernize-*,readability-*,performance-*,clang-analyzer-*,cppcoreguidelines-*,concurrency-*,misc-*,bugprone-*,google-*,hicpp-*")
project(${PROJECT_NAME})

message(STATUS "C++ compiler ID: ${CMAKE_CXX_COMPILER_ID}")

# Set the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
endif()

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

# Add the include directory to the include path
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)


add_custom_target(tidy
        COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} ${SRC_FILES} -- -I${CMAKE_SOURCE_DIR}/include -I${croncpp_SOURCE_DIR}/include
        # DEPENDS ${SRC_FILES} ${HEADER_FILES}
        COMMENT "Running clang-tidy"
        )
