# Get all the .cpp files in the src directory
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create an executable from the source files
add_executable(my_client ${SRC_FILES})

# Link the executable against the library
target_link_libraries(my_client PRIVATE ${PROJECT_NAME})
target_include_directories(my_client PRIVATE ${croncpp_SOURCE_DIR}/include)
target_include_directories(my_client PRIVATE ${CMAKE__SOURCE_DIR}/lib/include)

add_custom_target(tidy_cli_client
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} ${SRC_FILES} -- -I${croncpp_SOURCE_DIR}/include -I${CMAKE_SOURCE_DIR}/lib/include
    COMMENT "Running clang-tidy on the client source files"
)
