#include"EpollDemultiplexer.hpp"
#include"EventHandler.hpp"

#include<sys/epoll.h>
#include<unistd.h>

EpollDemultiplexer::EpollDemultiplexer():activeEventList(EventListSize)
{
    epfd=epoll_create1(EPOLL_CLOEXEC);
}

EpollDemultiplexer::~EpollDemultiplexer()
{
    close(epfd);
}

void EpollDemultiplexer::regHandler(EventHandler* handler)
{
    epoll_event evt;
    evt.events=handler->getevents();
    evt.data.ptr=handler;
    int op;
    if(handler->isInEpoll)
    {
        op=EPOLL_CTL_MOD;
    }
    else
    {
        op=EPOLL_CTL_ADD;
    }
    handler->isInEpoll=true;
    int ret=epoll_ctl(epfd,op,handler->getfd(),&evt);
    if(ret<0)
    {
        cout<<"Error: epoll_ctl ADD on fd "<<handler->getfd()<<endl;
    }
    else
    {
        cout<<"Success: epoll_ctl on fd "<<handler->getfd()<<endl;
    }
}

void EpollDemultiplexer::remHandler(EventHandler* handler)
{
    if(!handler->isInEpoll)
    {
        abort;
    }
    else
    {
        handler->isInEpoll=false;
        int op=EPOLL_CTL_DEL;
        int ret=epoll_ctl(epfd,op,handler->getfd(),NULL);
        if(ret<0)
        {
            cout<<"Error: epoll_ctl DEL on fd "<<handler->getfd()<<endl;
        }
        handler->isInEpoll=false;
    }
}

vector<EventHandler*> EpollDemultiplexer::fillactiveEventList(int activeNum)
{
    vector<EventHandler*> tempEventList;
    for(int i=0;i<activeNum;i++)
    {
        EventHandler* evthandler=static_cast<EventHandler*>(activeEventList[i].data.ptr);
        if(activeEventList[i].events & EPOLLIN)
        {
            evthandler->_revents=EPOLLIN;
        }
        if(activeEventList[i].events & EPOLLOUT)
        {
            evthandler->_revents=EPOLLOUT;
        }
        tempEventList.push_back(evthandler);
    }
    return tempEventList;
}

vector<EventHandler*> EpollDemultiplexer::epoll()
{
    vector<EventHandler*> tempEventList;
    int nfds=epoll_wait(epfd,activeEventList.data(),activeEventList.size(),-1);
    if(nfds>0)
    {
        tempEventList=fillactiveEventList(nfds);
        if(nfds==activeEventList.size())
        {
            activeEventList.resize(activeEventList.size()*2);
        }
    }
    else if (nfds==0)
    {
        
    }
    else
    {
        cout<<"Error: nfds= "<<nfds<<endl;
    }
    return tempEventList;
}
