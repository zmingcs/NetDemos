#include"Timer.hpp"
#include"TimeWheel.hpp"
#include<functional>
#include<iostream>
using namespace std;

void fun100()
{
    cout << "This is func 100" << endl;
}
void fun200()
{
    cout << "This is func 200" << endl;
}
void fun500()
{
    cout << "This is func 500" << endl;
}

void fun1500()
{
    cout << "This is func 1500" << endl;
}

int main()
{
    function<void(void)> f100 = bind(&fun100);
    function<void(void)> f200 = bind(&fun200);
    function<void(void)> f500 = bind(&fun500);
    function<void(void)> f1500 = bind(&fun1500);
    
    TimeWheel timewheel(100,10);
    Timer timer1(1,100,f100);
    Timer timer2(2,200,f200);
    Timer timer3(3,500,f500);
    Timer timer4(4,1500,f1500);

    bool isTrue=true;
    int nloop=0;
    while(1)
    {
        this_thread::sleep_for(chrono::milliseconds(200));
        if(isTrue)
        {
            timewheel.AddTimer(timer1);
            timewheel.AddTimer(timer2);
            timewheel.AddTimer(timer3);
            timewheel.AddTimer(timer4);
            isTrue=false;
        }
    }
    
    
    
}
