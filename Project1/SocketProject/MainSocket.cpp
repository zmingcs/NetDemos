//
//  MainSocket.cpp
//  SocketProject
//
//  Created by 小明 on 2020/5/23.
//  Copyright © 2020 小明. All rights reserved.
//

#include "MainSocket.hpp"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;


int Socket::socketcreate(int family,int type,int protocal)
{
    socket_=socket(family,type,protocal);
    if(socket_==-1)
    {
        cout<<"Error: tcpsocket"<<endl;
        return 1;
    }
    else
    {
        cout<<"Succeess: socketcreate"<<endl;
        return 0;
    }
}
int Socket::socketbind(string ip,int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (ip == "")
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        addr.sin_addr.s_addr = inet_addr(ip.data());
    
    if(::bind(socket_,(struct sockaddr *)&addr,sizeof(struct sockaddr_in))==-1)
    {
        cout<<"Error: bind"<<endl;
        return 1;
    }
    else
    {
        cout<<"Succeess: socketbind"<<endl;
        return 0;
    }
}
int Socket::socketconnect(string ip,int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.data());
    if (connect(socket_, (const struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        cout<<"Error: connect"<<endl;
        return 1;
    }
    else
    {
        cout<<"Succeess: socketconnect"<<endl;
        return 0;
    }

}
int Socket::socketlisten(int backlog)
{
    if(listen(socket_,backlog)<0)
    {
        cout<<"Error: listen"<<endl;
        return 1;
    }
    else
    {
        cout<<"Succeess: socketlisten"<<endl;
        return 0;
    }
}
int Socket::socketaccept(struct sockaddr_in clientaddr)
{
    socklen_t clnt_addr_size = sizeof(clientaddr);
    if(accept(socket_,(struct sockaddr*)&clientaddr,&clnt_addr_size) ==-1)
    {
        cout<<"Error: socketaccept"<<endl;
        return 1;
    }
    else
    {
        cout<<"Succeess: socketaccept"<<endl;
        return 0;
    }
}
int Socket::getfd() const
{
    return socket_;
}
void Socket::socketclose(int socketid)
{
    close(socketid);
}
void Socket::socketclose()
{
    close(socket_);
}

