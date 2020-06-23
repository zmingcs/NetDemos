cmake_minimum_required(VERSION 2.8)
project (demo)
add_executable(TCPServer TCPServer.cpp TCPSocket.cpp MainSocket.cpp)
add_executable(TCPClient TCPClient.cpp TCPSocket.cpp MainSocket.cpp)
