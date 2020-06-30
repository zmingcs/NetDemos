#include"EventHandler.hpp"
#include<sys/epoll.h>

EventHandler::EventHandler(int _fd):fd(_fd),_events(0),_revents(0),isInEpoll(0),size(0){}

EventHandler::~EventHandler(){}

void EventHandler::handleEvent()
{
    if(_revents&EPOLLIN)
    {
        readCallback(fd);
    }
    if(_revents&EPOLLOUT)
    {
        writeCallback(fd);
    }
}

void EventHandler::setreadCallback(EventCallback cb)
{
    readCallback=cb;
}

void EventHandler::setwriteCallback(EventCallback cb)
{
    writeCallback=cb;
}

void EventHandler::setcloseCallback(EventCallback cb)
{
    closeCallback=cb;
}

void EventHandler::enableRead()
{
    _events=EPOLLIN;
}

void EventHandler::enableWrite()
{
    _events=EPOLLOUT;
}

void EventHandler::enableAll()
{
    _events|=EPOLLIN;
    _events|=EPOLLOUT;
}

void EventHandler::disableAll()
{
    _events=0;
}
