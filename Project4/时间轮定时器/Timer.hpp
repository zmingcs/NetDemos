#ifndef Timer_hpp
#define Timer_hpp

#include<iostream>
#include<functional>
#include<list>
#include<thread>
#include<mutex>
using namespace std;

typedef struct TimerPos_
{
    int ms_pos;
    int s_pos;
    int min_pos;
}TimerPos;



class Timer
{
private:
    int timerid;
    int timerspan;
    TimerPos timerpos;
public:
    Timer();
    Timer(int id,int span,function<void(void)> fun);
    ~Timer(){};
    function<void(void)> callback;
    int get_timerid();
    int set_timerid(int id);
    int get_timerspan();
    int set_timerspan(int span);
    TimerPos get_timerpos();
    int set_timerpos(TimerPos pos);
};




#endif /* Timer_hpp */
