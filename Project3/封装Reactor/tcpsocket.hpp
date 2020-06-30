#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<iostream>
using namespace std;

class TcpSocket
{
private:
    int socket_;
public:
    TcpSocket(){}

    int getSockFd()
    {
        return socket_;
    }

    int setSockFd(int sockfd)
    {
        socket_=sockfd;
        return 0;
    }

    int createSocket()
    {
        socket_=socket(AF_INET, SOCK_STREAM, 0);
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

    int bindSocket(int socketid,string ip,int port)
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        if (ip == "")
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
        else
            addr.sin_addr.s_addr = inet_addr(ip.data());
        
        if(::bind(socketid,(struct sockaddr *)&addr,sizeof(struct sockaddr_in))==-1)
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

    int listenSocket(int socketid,int backlog)
    {
        if(listen(socketid,backlog)<0)
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

    int acceptSocket(TcpSocket &csock)
    {
        struct sockaddr_in clientaddr;
        socklen_t clnt_addr_size = sizeof(clientaddr);
        int clint_sock=accept(socket_,(struct sockaddr*)&clientaddr,&clnt_addr_size);
        if(clint_sock==-1)
        {
            cout<<"Error: socketaccept"<<endl;
            return -1;
        }
        csock.setSockFd(clint_sock);
        return 0;
    }

    int connectSocket(string ip,int port)
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

    bool receiveInfo(std::string &buf)
    {
        char tmp[4096] = {0};
        int ret = recv(socket_, tmp, 4096, 0);
        if (ret < 0)
        {
            cout<<"Error: receiveInfo"<<endl;
            return false;
        }
        else if (ret == 0)
        {
            cout<<"Error: client shutdown"<<endl;
            return false;
        }
        buf.assign(tmp, ret);
        return true;
    }
    bool sendInfo(std::string &buf)
    {
        int ret = send(socket_, buf.data(), buf.size(), 0);
        if (ret < 0)
        {
            cout<<"Error: sendInfo"<<endl;
            return false;
        }
        return true;
    }

    void closeSocket()
    {
        close(socket_);
        socket_=-1;
    }
};

