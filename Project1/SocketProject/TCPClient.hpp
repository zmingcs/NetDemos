//
//  TCPClient.hpp
//  SocketProject
//
//  Created by 小明 on 2020/5/23.
//  Copyright © 2020 小明. All rights reserved.
//

#ifndef TCPClient_hpp
#define TCPClient_hpp

#include"TCPSocket.hpp"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

class TCPClient:public TCPSocket
{
public:
    TCPClient(string ip,int port)
    {
        socketcreate(AF_INET, SOCK_STREAM, 0);
        socketconnect(ip,port);
    }
    ~TCPClient(){}
};

#endif /* TCPClient_hpp */
