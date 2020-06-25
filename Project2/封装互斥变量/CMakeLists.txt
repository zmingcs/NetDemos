cmake_minimum_required(VERSION 2.8)
project (demo)
add_executable(pthread_mutex pthread_mutex.cpp)
find_package(Threads)
target_link_libraries(pthread_mutex ${CMAKE_THREAD_LIBS_INIT})

