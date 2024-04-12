cmake_minimum_required(VERSION 3.27)
project(pdp)

set(CMAKE_CXX_STANDARD 14)

add_executable(pdp
        "Shared Memory/threads.cpp"
        "Shared Memory/thread_guard.cpp")
