//
//  MainSocket.hpp
//  SocketProject
//
//  Created by 小明 on 2020/5/23.
//  Copyright © 2020 小明. All rights reserved.
//

#ifndef MainSocket_hpp
#define MainSocket_hpp

#include <iostream>
using namespace std;

class Socket
{
private:
    int socket_;
public:
    Socket(){};
    virtual int socketcreate(int family,int type,int protocal);;
    virtual int socketbind(string ip,int port);
    virtual int socketconnect(string ip,int port);
    virtual int socketlisten(int backlog);
    virtual int socketaccept(struct sockaddr_in clientaddr);
    virtual int getfd() const;
    virtual void socketclose(int socketid);
    virtual void socketclose();
    virtual ~Socket(){};
};



#endif /* MainSocket_hpp */
