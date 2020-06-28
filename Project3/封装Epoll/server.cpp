#include <iostream>
#include <vector>
#include <sys/epoll.h>
#include "tcpsocket.hpp"
#include <fcntl.h>
class MyEpoll 
{
private:
    int epfd;
public:
    void setNoblockingMode(int fd)
    {
        fcntl(fd,F_SETFL,fcntl(fd,F_GETFL,0)|O_NONBLOCK);
    }
    int createEpoll() 
    {
        epfd = epoll_create(5);
        if (epfd < 0) {
            cout<<"Error: createEpoll"<<endl;
            return -1;
        }
        return 0;
    }
    int addEpoll(TcpSocket sock, uint32_t events = 0)
    {
        int fd = sock.getSockFd();
        setNoblockingMode(fd);
        //定义事件
        struct epoll_event ev;
        ev.events = EPOLLIN | events;
        ev.data.fd = fd;
        
        int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
        if (ret < 0) {
            cout<<"Error: addEpoll"<<endl;
            return -1;
        }
        return 0;
    }
    int delEpoll(TcpSocket sock) 
    {
        int fd = sock.getSockFd();
        int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
        if (ret < 0) 
        {
            cout<<"Error: delEpoll"<<endl;
            return -1;
        }
        return 0;
    }
    int waitEpoll(std::vector<TcpSocket> &list, int ms_timeout = 20000000)
    {
        struct epoll_event evs[20];
        int nfds = epoll_wait(epfd, evs, 20, ms_timeout);
        if (nfds < 0) 
        {
            cout<<"Error: waitEpoll"<<endl;
            return -1;
        }
        else if (nfds == 0) 
        {
            cout<<"Error: waitEpoll timeout"<<endl;
            return -1;
        }
        for (int i = 0; i < nfds; i++) 
        {
            int fd = evs[i].data.fd;
            TcpSocket sock;
            sock.setSockFd(fd);
            list.push_back(sock);
        }
        return 0;
    }
};

int main(){
    TcpSocket serversock;            
    serversock.createSocket();
    serversock.bindSocket("127.0.0.1",1244);
    serversock.listenSocket(20);

    MyEpoll epoll;
    epoll.createEpoll();
    epoll.addEpoll(serversock, EPOLLET);
    while(1) 
    {
        vector<TcpSocket> list;
        int ret = epoll.waitEpoll(list);
        if (ret == -1) 
        {
            continue;
        }
        for (int i = 0; i < list.size(); i++) 
        {
            if (list[i].getSockFd() == serversock.getSockFd()) 
            {
                TcpSocket clientsock;
                serversock.acceptSocket(clientsock);
                epoll.addEpoll(clientsock, EPOLLET);
            }
            else 
            {
                string buf;
                if(list[i].receiveInfo(buf)==true) 
                    cout << "client "<<list[i].getSockFd()<< " say: " << buf << std::endl;
                else
                {
                    return -1;
                }
                
            }
        }
    }
    serversock.closeSocket();
    return 0;
}

