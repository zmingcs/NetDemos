#include<functional>
#include<iostream>
using namespace std;
#define MAX_BUFFSIZE 1024
typedef std::function<void(int )> EventCallback;

class EventHandler
{
private:
    int fd;
    int _events;
    int _revents;
    bool isInEpoll;
    char buff[MAX_BUFFSIZE];
    int size;
    EventCallback readCallback;
    EventCallback writeCallback;
    EventCallback closeCallback;
public:
    friend class EpollDemultiplexer;
    EventHandler(int);
    ~EventHandler();
    void handleEvent();
    void setreadCallback(EventCallback);
    void setwriteCallback(EventCallback);
    void setcloseCallback(EventCallback);

    void enableRead();
    void enableWrite();
    void enableAll();
    void disableAll();

    int getfd()
    {
        return fd;
    }

    int getevents()
    {
        return _events;
    }

    int getrevents()
    {
        return _revents;
    }

    char* getbuff()
    {
        return buff;
    }

    void setsize(int sz)
    {
        size=sz;
    }

    int getsize()
    {
        return size;
    }
};
