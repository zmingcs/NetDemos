//
//  TCPSocket.cpp
//  SocketProject
//
//  Created by 小明 on 2020/5/23.
//  Copyright © 2020 小明. All rights reserved.
//

#include "TCPSocket.hpp"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

    
int TCPSocket::tcpsocketaccept(struct sockaddr_in clientaddr)
{

    socklen_t clnt_addr_size = sizeof(clientaddr);
    int clint_sock=accept(this->getfd(),(struct sockaddr*)&clientaddr,&clnt_addr_size);
    if(clint_sock==-1)
    {
        cout<<"Error: tcpsocketaccept"<<endl;
        return -1;
    }
    else
        return clint_sock;
}
int TCPSocket::tcpsend(int sock,string message)
{
    write(sock, message.data(), sizeof(message.data())+100);
    return 0;
}
int TCPSocket::tcpreceive(int sock,char* message)
{
    return read(sock,message, sizeof(message)+100);
}


