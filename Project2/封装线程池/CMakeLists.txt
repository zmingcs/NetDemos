cmake_minimum_required(VERSION 2.8)
project (demo)
add_executable(ThreadPool ThreadPool.cpp)
find_package(Threads)
target_link_libraries(ThreadPool ${CMAKE_THREAD_LIBS_INIT})

