set(CLIENT_NAME cli)

# Get all the .cpp files in the src directory
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Create an executable from the source files
add_executable(${CLIENT_NAME} ${SRC_FILES})

# Link the executable against the library
target_link_libraries(${CLIENT_NAME} PRIVATE ${PROJECT_NAME})
target_include_directories(${CLIENT_NAME} PRIVATE ${croncpp_SOURCE_DIR}/include)

add_custom_target(tidy_cli_client
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} ${SRC_FILES} -- -I${croncpp_SOURCE_DIR}/include -I${CMAKE_SOURCE_DIR}/lib/include
    COMMENT "Running clang-tidy on the client source files"
)
