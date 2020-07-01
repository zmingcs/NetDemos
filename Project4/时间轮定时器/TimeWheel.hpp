#ifndef TimeWheel_hpp
#define TimeWheel_hpp
#include"Timer.hpp"
#include <iostream>
using namespace std;

class TimeWheel
{
private:
    TimerPos managertime;
    int mscnt=0;
    int scnt=0;
    int mincnt=0;
    
    int timercnt=0;
    
    int step_time=0;
    
    mutex _mutex;
    list<Timer> *callbacklist=nullptr;
public:
    TimeWheel();
    TimeWheel(int step,int minute);
    ~TimeWheel(){};
    
    int AddTimer(Timer &timer);
    int DeleteTimer(int timerid);
    int drive();
    int run(list<Timer> timer);
    int totalTimers();
};








#endif /* TimeWheel_hpp */
