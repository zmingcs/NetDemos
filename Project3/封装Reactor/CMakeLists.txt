cmake_minimum_required(VERSION 3.5)
project(my_muduo_net)

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

add_compile_options("-std=c++11")

set(net_SRCS 
    main.cpp
    EventHandler.cpp
    EpollDemultiplexer.cpp
    Reactor.cpp
    )

add_executable(server ${net_SRCS})
add_executable(client client.cpp)
