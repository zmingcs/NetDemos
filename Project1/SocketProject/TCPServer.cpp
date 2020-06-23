//
//  TCPServer.cpp
//  SocketProject
//
//  Created by 小明 on 2020/5/23.
//  Copyright © 2020 小明. All rights reserved.
//

#include "TCPServer.hpp"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;



int main()
{
    TCPServer tss("127.0.0.1",1236);
    struct sockaddr_in clnt_addr;
    int clint_sock=tss.tcpsocketaccept(clnt_addr);

    string whattosend;
    char whatget[400];
    while(tss.tcpreceive(clint_sock, whatget)>0)
    {
        whattosend=whatget;
        cout<<"server gets: \n"<<whattosend<<endl;
        tss.tcpsend(clint_sock,whattosend);
    }

    tss.socketclose(clint_sock);
    tss.socketclose();
    return 0;
}

