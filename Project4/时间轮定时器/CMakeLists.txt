cmake_minimum_required(VERSION 2.8)
project (demo)
add_executable(main main.cpp TimeWheel.cpp Timer.cpp)
find_package(Threads)
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})

