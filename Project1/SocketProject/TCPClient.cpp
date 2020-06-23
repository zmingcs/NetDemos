//
//  TCPClient.cpp
//  SocketProject
//
//  Created by 小明 on 2020/5/23.
//  Copyright © 2020 小明. All rights reserved.
//

#include "TCPClient.hpp"
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
    
    TCPClient tsc("127.0.0.1",1236);
    string whattosend,whattoreceive="begin";
    while(true)
    {
        cout<<"what to send: "<<endl;
        getline(cin,whattosend);
        if(whattosend.compare("quit")==0)
            break;
        tsc.tcpsend(tsc.getfd(),whattosend);
        char whatget[400];
        tsc.tcpreceive(tsc.getfd(),whatget);
        whattoreceive=whatget;
        cout<<"what to receive: "<<endl;
        cout<<whattoreceive<<endl;
    }
    
    tsc.socketclose();
    return 0;
}
