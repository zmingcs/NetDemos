#include<sys/epoll.h>
#include<memory>
#include<vector>
#include<iostream>
using namespace std;


class EventHandler;
class EpollDemultiplexer
{
    typedef vector<epoll_event> EventList;
private:
    int epfd;
    EventList activeEventList;
    vector<EventHandler*> fillactiveEventList(int activeNum);
public:
    EpollDemultiplexer();
    ~EpollDemultiplexer();
    void regHandler(EventHandler* handler);
    void remHandler(EventHandler* handler);
    vector<EventHandler*> epoll();
    static const int EventListSize=20;
};

