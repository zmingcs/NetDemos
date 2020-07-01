#include "TimeWheel.hpp"
#include<cstring>
#include<iostream>
using namespace std;

TimeWheel::TimeWheel()
{
    memset(&managertime,0,sizeof(managertime));
}

TimeWheel::TimeWheel(int step,int minute)
{
    if(1000%step!=0)
    {
        cout<<"step is not proper, it should be divided by 1000"<<endl;
    }
    step_time=step;
    mscnt=1000/step;
    scnt=60;
    mincnt=minute;
    
    callbacklist=new list<Timer>[mscnt+scnt+mincnt];
    thread th([&]
    {
        this->drive();
    });
    th.detach();
}

int TimeWheel::AddTimer(Timer &timer)
{
    int timespan=timer.get_timerspan();
    if(timespan<step_time||timespan%step_time!=0||timespan>=step_time*mscnt*scnt*mincnt)
    {
        cout<<"timespan is invalid!"<<endl;
        return -1;
    }
    unique_lock<mutex> lock(_mutex);
    timer.set_timerpos(managertime);
    
    TimerPos tmppos={0};
    int cur_time=step_time*managertime.ms_pos+managertime.s_pos*1000+managertime.min_pos*60*1000;
    int future_time=cur_time+timespan;
    tmppos.min_pos=(future_time/1000/60)%mincnt;
    tmppos.s_pos=(future_time%(1000*60))/1000;
    tmppos.ms_pos=(future_time%1000)/step_time;
    
    if(tmppos.min_pos!=managertime.min_pos)
    {
        callbacklist[mscnt+scnt+tmppos.min_pos].push_back(timer);
    }
    else if(tmppos.s_pos!=managertime.s_pos)
    {
        callbacklist[mscnt+tmppos.s_pos].push_back(timer);
    }
    else if(tmppos.ms_pos!=managertime.ms_pos)
    {
        callbacklist[tmppos.ms_pos].push_back(timer);
    }
    
    timercnt++;
    cout<<"Success: Add a timer ---timer's id is: "<<timer.get_timerid()<<endl;
    return timer.get_timerid();
}

int TimeWheel::DeleteTimer(int timerid)
{
    unique_lock<mutex> lock(_mutex);
    int i=0;
    int ncnt=mscnt+scnt+mincnt;
    for(i=0;i<ncnt;i++)
    {
        list<Timer>& tmptimer=callbacklist[i];
        for(auto item=tmptimer.begin();item!=tmptimer.end();item++)
        {
            if(item->get_timerid()==timerid)
            {
                item=tmptimer.erase(item);
                return 0;
            }
        }
    }
    if(i==ncnt)
    {
        cout<<"The timer is not found!"<<endl;
        return -1;
    }
    timercnt--;
    return 0;
}


int TimeWheel::drive()
{
    cout<<"start run"<<endl;
    static int ncnt=0;
    while(true)
    {
        this_thread::sleep_for(chrono::milliseconds(step_time));
        unique_lock<mutex> lock(_mutex);
        cout<<"No."<<ncnt++<<" tick"<<endl;
        TimerPos tmppos={0};
        TimerPos lastpos=managertime;
        
        int cur_time=step_time*managertime.ms_pos+managertime.s_pos*1000+managertime.min_pos*60*1000;
        int future_time=cur_time+step_time;
        tmppos.min_pos=(future_time/1000/60)%mincnt;
        tmppos.s_pos=(future_time%(1000*60))/1000;
        tmppos.ms_pos=(future_time%1000)/step_time;
        
        managertime=tmppos;
        
        if(tmppos.min_pos!=lastpos.min_pos)
        {
            list<Timer>& tmptimer=callbacklist[managertime.min_pos+scnt+mscnt];
            run(tmptimer);
            tmptimer.clear();
        }
        else if(tmppos.s_pos!=lastpos.s_pos)
        {
            list<Timer>& tmptimer=callbacklist[managertime.s_pos+mscnt];
            run(tmptimer);
            tmptimer.clear();
        }
        else if(tmppos.ms_pos!=lastpos.ms_pos)
        {
            list<Timer>& tmptimer=callbacklist[managertime.ms_pos];
            run(tmptimer);
            tmptimer.clear();
        }
        else
        {
            cout<<"Error: time is not changed!"<<endl;
            return -1;
        }
        lock.unlock();
    }
    return 0;
}

int TimeWheel::run(list<Timer> timer)
{
    for(auto item=timer.begin();item!=timer.end();item++)
    {
        int cur_time=step_time*managertime.ms_pos+managertime.s_pos*1000+managertime.min_pos*60*1000;
        int last_time=step_time*item->get_timerpos().ms_pos+item->get_timerpos().s_pos*1000+item->get_timerpos().min_pos*60*1000;
        int gap=(cur_time-last_time+(mincnt+1)*60*1000)%((mincnt+1)*60*1000);
        if(gap==item->get_timerspan())
        {
            item->callback();
            item->set_timerpos(managertime);
            /**/
            TimerPos tmppos={0};
            int cur_time=step_time*managertime.ms_pos+managertime.s_pos*1000+managertime.min_pos*60*1000;
            int future_time=cur_time+item->get_timerspan();
            tmppos.min_pos=(future_time/1000/60)%mincnt;
            tmppos.s_pos=(future_time%(1000*60))/1000;
            tmppos.ms_pos=(future_time%1000)/step_time;
            
            if(tmppos.min_pos!=managertime.min_pos)
            {
                callbacklist[mscnt+scnt+tmppos.min_pos].push_back(*item);
            }
            else if(tmppos.s_pos!=managertime.s_pos)
            {
                callbacklist[mscnt+tmppos.s_pos].push_back(*item);
            }
            else if(tmppos.ms_pos!=managertime.ms_pos)
            {
                callbacklist[tmppos.ms_pos].push_back(*item);
            }
            /**/
        }
        else
        {
            TimerPos tmppos={0};
            int cur_time=step_time*managertime.ms_pos+managertime.s_pos*1000+managertime.min_pos*60*1000;
            int future_time=cur_time+item->get_timerspan()-gap;
            tmppos.min_pos=(future_time/1000/60)%mincnt;
            tmppos.s_pos=(future_time%(1000*60))/1000;
            tmppos.ms_pos=(future_time%1000)/step_time;
            
            if(tmppos.min_pos!=managertime.min_pos)
            {
                callbacklist[mscnt+scnt+tmppos.min_pos].push_back(*item);
            }
            else if(tmppos.s_pos!=managertime.s_pos)
            {
                callbacklist[mscnt+tmppos.s_pos].push_back(*item);
            }
            else if(tmppos.ms_pos!=managertime.ms_pos)
            {
                callbacklist[tmppos.ms_pos].push_back(*item);
            }
        }
    }
    return 0;
}

int TimeWheel::totalTimers()
{
    return timercnt;
}
