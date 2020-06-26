cmake_minimum_required(VERSION 2.8)
project (demo)
add_executable(condThread condThread.cpp)
find_package(Threads)
target_link_libraries(condThread ${CMAKE_THREAD_LIBS_INIT})

