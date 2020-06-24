cmake_minimum_required(VERSION 2.8)
project (demo)
add_executable(createThread createThread.cpp)
find_package(Threads)
target_link_libraries(createThread ${CMAKE_THREAD_LIBS_INIT})

