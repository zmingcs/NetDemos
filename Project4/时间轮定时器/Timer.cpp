#include "Timer.hpp"
#include <iostream>
using namespace std;

Timer::Timer(int id,int span,function<void(void)> fun)
{
    timerid=id;
    timerspan=span;
    callback=fun;
}

int Timer::get_timerid()
{
    return timerid;
}

int Timer::set_timerid(int id)
{
    timerid=id;
    return 0;
}

int Timer::get_timerspan()
{
    return timerspan;
}

int Timer::set_timerspan(int span)
{
    timerspan=span;
    return 0;
}

TimerPos Timer::get_timerpos()
{
    return timerpos;
}

int Timer::set_timerpos(TimerPos pos)
{
    timerpos=pos;
    return 0;
}
