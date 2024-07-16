# cmake minimum required version should be at least 3.14
cmake_minimum_required(VERSION 3.14)

# Project name
project(pdp)

# GoogleTest requires at least C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMake policy to avoid warnings
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# Option to use pre-downloaded GoogleTest
option(USE_PREDOWNLOADED_GTEST "Use pre-downloaded GoogleTest" OFF)

if(USE_PREDOWNLOADED_GTEST)
    # Set GoogleTest directories
    set(GTEST_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/googletest/googletest/include)
    set(GTEST_LIBRARY ${CMAKE_SOURCE_DIR}/thirdparty/googletest/lib/libgtest.a)
    set(GTEST_MAIN_LIBRARY ${CMAKE_SOURCE_DIR}/thirdparty/googletest/lib/libgtest_main.a)

    # Add GoogleTest include directory
    include_directories(${GTEST_INCLUDE_DIR})
else()
    # Fetch GoogleTest from GitHub
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/e39786088138f2749d64e9e90e0f9902daa77c40.zip
    )
    FetchContent_MakeAvailable(googletest)

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    # Link GoogleTest libraries
    set(GTEST_LIBRARY GTest::gtest)
    set(GTEST_MAIN_LIBRARY GTest::gtest_main)
endif()

# Enable testing
enable_testing()

# Define executables
add_executable(threads "shared-memory/threads.cpp" "shared-memory/thread_guard.cpp")
add_executable(move_semantic "shared-memory/move_semantics.cpp")
add_executable(mem_consistent
        shared-memory/mem_consistent.cpp
        shared-memory/mem_consistent_no_fences.cpp
)

# Set a variable to hold test executables
set(TEST_EXECUTABLES)

# Find all test source files
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false "shared-memory/tests/*.cpp")

# Loop through test source files and create executables
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Get the filename without directory
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    # Create an executable for the test
    add_executable(${TEST_NAME} ${TEST_SOURCE})

    # Link the executable with GoogleTest libraries
    if(USE_PREDOWNLOADED_GTEST)
        target_link_libraries(${TEST_NAME} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} pthread)
    else()
        target_link_libraries(${TEST_NAME} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
    endif()

    # Register the test with CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    # Add the test executable to the list
    list(APPEND TEST_EXECUTABLES ${TEST_NAME})
endforeach()

# Discover and register all tests
include(GoogleTest)
gtest_discover_tests(${TEST_EXECUTABLES})