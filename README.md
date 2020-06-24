# NetDemos
Demos are created for UESTC_Networking_Programming_Experiments_Course. 
Four projects included explore computer network programming and I/O multiplexing: Socket Encapsulation, Thread/ThreadPool, Epoll/Reactor and TimeWheel.  

## How to use
All the programs are recommended to be compiled by CMake in Linux for convenience'sake as the CMakeLists.txt in each project has been edited properly.

Take Project1 as an example:
1. open a terminal in Linux and switch the current working path to '/Project1/SocketProject'.
2. run '**cmake .**'.
3. run '**make**', then *TCPServer* and *TCPClient* should be produced.
4. run '**./TCPServer**' to boot the server.
5. open another terminal in current working path and run '**./TCPClient**' to boot the client.
6. input words in client terminal then the server should receive and return the same words.
7. input '**quit**' in client terminal and the connection will be cut off.

Other programs run in same way. The CMakeLists.txt can be edited when needed.

## Note
All the demos are initially created for a course and there must be some mistakes.
