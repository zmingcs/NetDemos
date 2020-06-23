//
//  TCPServer.hpp
//  SocketProject
//
//  Created by 小明 on 2020/5/23.
//  Copyright © 2020 小明. All rights reserved.
//

#ifndef TCPServer_hpp
#define TCPServer_hpp

#include"TCPSocket.hpp"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
class TCPServer:public TCPSocket
{
public:
    TCPServer(string ip,int port)
    {
        socketcreate(AF_INET, SOCK_STREAM, 0);
        socketbind(ip,port);
        socketlisten(20);
    }
    ~TCPServer(){}
};
#endif /* TCPServer_hpp */
