
set(TEST_NAME test)


FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
        )
FetchContent_MakeAvailable(googletest)


# Find Google Test
# find_package(GTest REQUIRED)
enable_testing()

# Include Google Test headers
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB TEST_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# Add test executable
add_executable(${TEST_NAME} ${TEST_SRC_FILES})

# Link against Google Test
# target_link_libraries(${TEST_NAME} ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${TEST_NAME} GTest::gtest_main ${PROJECT_NAME})
target_include_directories(${TEST_NAME} PRIVATE ${croncpp_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})

# set(OBJECT_DIR ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/test.dir)

find_program(LCOV_PATH lcov)
if(NOT LCOV_PATH)
    message(WARNING "lcov not found! You won't be able to generate coverage reports.")
endif()

get_target_property(LIB_BINARY_DIR JobHeap BINARY_DIR)

add_custom_target(coverage
# COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${LIB_BINARY_DIR}/*.gcno
    COMMAND rm -f ${LIB_BINARY_DIR}/*.gcda
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
#     COMMAND gcov -r -b -t -l ${TEST_SRC_FILES} -o ${OBJECT_DIR}
    COMMAND lcov --capture --all --quiet --directory ${LIB_BINARY_DIR} --output-file coverage.info --ignore-errors inconsistent,inconsistent,usage,range --filter range
    COMMAND lcov --remove --quiet coverage.info '/usr/*' '_deps/*' --output-file coverage.info # remove system libraries
    COMMAND lcov --list --quiet coverage.info
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)


