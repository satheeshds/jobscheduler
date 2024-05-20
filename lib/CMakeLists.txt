
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
# Get all the .cpp and .h files in the src and include directory
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${croncpp_SOURCE_DIR}/include)
# Add the include directory to the include path
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_custom_target(tidy_lib
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} ${SRC_FILES} -- -I${croncpp_SOURCE_DIR}/include -I${CMAKE_CURRENT_SOURCE_DIR}/include
    COMMENT "Running clang-tidy on the library source files"
)
