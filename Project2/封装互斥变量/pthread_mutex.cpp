#include <iostream>
#include<string>
#include<pthread.h>
using namespace std;

pthread_mutex_t mlock=PTHREAD_MUTEX_INITIALIZER;
int g_val=0;


class Thread
{
private:
    pthread_t threadid;
    static void * thread_proxy_func(void * args);
public:
    Thread(){};
    virtual void run(){};
    void start();
    void join();
    ~Thread(){};
};


void * Thread::thread_proxy_func(void * args)
{
    Thread * pThread = static_cast<Thread *>(args);
    pThread->run();
    return NULL;
}

void Thread::start()
{
    pthread_create(&threadid, NULL, thread_proxy_func, this);
}

void Thread::join()
{
    pthread_join(threadid, NULL);
}

class VarThread:public Thread
{
public:
    void run()
    {
        for(int i=0;i<500000;++i)
        {
            pthread_mutex_lock(&mlock);
            int tmp=g_val;
            g_val=tmp+1;
            pthread_mutex_unlock(&mlock);
        }
    }
};

int main()
{
    VarThread td1,td2;
    td1.start();
    td2.start();
    td1.join();
    td2.join();
    cout<<g_val<<endl;
    return 0;
}

