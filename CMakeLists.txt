# cmake minimum required version should be at least 3.14
cmake_minimum_required(VERSION 3.14)

# Project name
project(pdp)

# GoogleTest requires at least C++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags to use C++11 standard
set(CXXFLAGS -std=c++11)

# CMake policy to avoid warnings
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

# Fetch GoogleTest from Github
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/e39786088138f2749d64e9e90e0f9902daa77c40.zip
)
include(GoogleTest)

# Find GoogleTest package
find_package(GTest REQUIRED)

# Set the binary name
set(BINARY ${CMAKE_PROJECT_NAME})

# Find all source files
set(SOURCES)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

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

    # Link the executable with GoogleTest
    target_link_libraries(${TEST_NAME} GTest::gtest_main)

    # Add the test executable to the list
    list(APPEND TEST_EXECUTABLES ${TEST_NAME})
endforeach()

# Discover and register all tests
gtest_discover_tests(${TEST_EXECUTABLES})

# Enable testing
enable_testing()