#ifndef REACTOR_HPP_
#define REACTOR_HPP_

#include"EpollDemultiplexer.hpp"
#include<memory>
#include<iostream>
using namespace std;

class EventHandler;

class Reactor
{
private:
    unique_ptr<EpollDemultiplexer> epolldemultiplexer;
public:
    Reactor():epolldemultiplexer(new EpollDemultiplexer){};
    void registerHandler(EventHandler* handler);
    void removeHandler(EventHandler* handler);
    void loop();
};

#endif
