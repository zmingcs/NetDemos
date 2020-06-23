//
//  TCPSocket.hpp
//  SocketProject
//
//  Created by 小明 on 2020/5/23.
//  Copyright © 2020 小明. All rights reserved.
//

#ifndef TCPSocket_hpp
#define TCPSocket_hpp

#include"MainSocket.hpp"
#include <iostream>
using namespace std;
class TCPSocket:public Socket
{
public:
    TCPSocket(){cout<<"tcpsocket"<<endl;}
    virtual int tcpsocketaccept(struct sockaddr_in clientaddr);
    virtual int tcpsend(int sock,string message);
    virtual int tcpreceive(int sock,char* message);
    virtual ~TCPSocket(){};
};





#endif /* TCPSocket_hpp */
