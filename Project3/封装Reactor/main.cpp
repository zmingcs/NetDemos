#include"Reactor.hpp"
#include"EventHandler.hpp"
#include"tcpsocket.hpp"

#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<vector>
#include<string>
#include<map>
#include<memory>
#include<functional>
#include<iostream>
using namespace std;

class Server
{
    string ip;
    int port;
    unique_ptr<Reactor> reactor;
    map<int,shared_ptr<EventHandler>> handlerList;
public:
    Server(string ipaddr,int pt):ip(ipaddr),port(pt),reactor(new Reactor){}
    void start()
    {
        startup();
        reactor->loop();
    }

    void startup()
    {
        cout<<"Start"<<endl;
        TcpSocket tcpsocket;
        tcpsocket.createSocket();
        int socket_=tcpsocket.getSockFd();
        auto lhandler=make_shared<EventHandler>(socket_);
        handlerList[socket_]=lhandler;

        int reuse=1;
        setsockopt(lhandler->getfd(),SOL_SOCKET,SO_REUSEADDR,&reuse, sizeof reuse);
        int ret=tcpsocket.bindSocket(lhandler->getfd(),ip,port);
        ret=tcpsocket.listenSocket(lhandler->getfd(),20);
        lhandler->setreadCallback(std::bind(&Server::acceptConn,this,std::placeholders::_1));
        lhandler->enableRead();
        reactor->registerHandler(lhandler.get());
    }

    void acceptConn(int fd)
    {
        cout<<"in accept"<<endl;
        int cfd=accept4(fd,NULL,NULL,SOCK_NONBLOCK);
        if(cfd<0)
        {
            cout<<"Error:accept"<<endl;
            exit(-1);
        }
        auto connhandler=make_shared<EventHandler>(cfd);
        handlerList[cfd]=connhandler;
        connhandler->setreadCallback(std::bind(&Server::readData,this,std::placeholders::_1));
        connhandler->enableRead();
        reactor->registerHandler(connhandler.get());
    }

    void readData(int fd)
    {
        cout<<"readData"<<endl;
        auto rhandler=handlerList[fd];
        int nbytes=read(fd,rhandler->getbuff(),MAX_BUFFSIZE);
        if(nbytes>0)
        {
            rhandler->getbuff()[nbytes]=0;
            cout<<rhandler->getbuff()<<endl;
            rhandler->setsize(nbytes);
            rhandler->setwriteCallback(std::bind(&Server::sendData,this,std::placeholders::_1));
            rhandler->enableWrite();
            reactor->registerHandler(rhandler.get());
        }
        else if(nbytes==0)
        {
            cout<<"close fd"<<endl;
            close(fd);
            reactor->removeHandler(rhandler.get());
            handlerList.erase(fd);
        }
        else
        {
            close(fd);
            cout<<"Error:readData"<<endl;
            reactor->removeHandler(rhandler.get());
            handlerList.erase(fd);
        }
    }

    void sendData(int fd)
    {
        auto shandler=handlerList[fd];
        int nbytes=write(fd,shandler->getbuff(),shandler->getsize());
        if(nbytes>0)
        {
            shandler->setreadCallback(std::bind(&Server::readData,this,std::placeholders::_1));
            shandler->enableRead();
            reactor->registerHandler(shandler.get());
        }
        else
        {
            cout<<"Error:writeData"<<endl;
            close(fd);
            reactor->removeHandler(shandler.get());
            handlerList.erase(fd);
        }
    }
};

int main()
{
    string addr="127.0.0.1";
    Server myserver(addr,2346);
    myserver.start();
}
