cmake_minimum_required(VERSION 3.27)
project(pdp)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)


add_executable(threads
        "shared-memory/threads.cpp"
        "shared-memory/thread_guard.cpp"
)

add_executable(move_semantic
        "shared-memory/move_semantics.cpp"
)

add_executable(naive_queue
        shared-memory/naive_queue.h
        shared-memory/tests/test_naive_queue.cpp
)

add_executable(threadsafe_queue
        shared-memory/threadsafe_queue.h
        shared-memory/tests/test_threadsafe_queue.cpp
)


target_link_libraries(naive_queue gtest_main)
target_link_libraries(threadsafe_queue gtest_main)

add_test(naive shared-memory/tests/test_naive_queue.cpp)
add_test(thr shared-memory/tests/test_threadsafe_queue.cpp)





