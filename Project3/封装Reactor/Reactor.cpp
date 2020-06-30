#include"Reactor.hpp"
#include"EventHandler.hpp"

#include<iostream>
using namespace std;

void Reactor::registerHandler(EventHandler* handler)
{
    epolldemultiplexer->regHandler(handler);
}

void Reactor::removeHandler(EventHandler* handler)
{
    epolldemultiplexer->remHandler(handler);
}

void Reactor::loop()
{
    while(1)
    {
        auto activeEventPtrList=epolldemultiplexer->epoll();
        if(!activeEventPtrList.empty())
        {
            for(int i=0;i<activeEventPtrList.size();i++)
            {
                activeEventPtrList[i]->handleEvent();
            }
        }
    }
};
