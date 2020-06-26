#include<iostream>
#include <cstdlib>
#include<pthread.h>
#include<unistd.h>
using namespace std;

pthread_mutex_t mlock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

typedef struct node
{
    int _data;
    struct node* _next;
}node_t,*node_p,**node_pp;

node_p head=NULL;

node_p alloc_node(int data)
{
    node_p ret=(node_p)malloc(sizeof(node_t));
    ret->_data=data;
    ret->_next=NULL;
    return ret;
}

void init(node_pp phead)
{
    *phead=alloc_node(0);
}

void push_front(node_p head, int data)
{
    node_p tmp=alloc_node(data);
    tmp->_next=head->_next;
    head->_next=tmp;
}

void pop_front(node_p head, int *pdata)
{
    if(head->_next!=NULL)
    {
        node_p tmp=head->_next;
        head->_next=tmp->_next;
        *pdata=tmp->_data;
        free(tmp);
    }
}

void show(node_p head)
{
    node_p cur=head->_next;
    while(cur)
    {
        cout<<cur->_data<<"->";
        cur=cur->_next;
    }
    cout<<endl;
}

//void* consumer(void *argv)
//{
//    int data;
//    while(1)
//    {
//        pthread_mutex_lock(&mlock);
//        while(head->_next==NULL)
//        {
//            cout<<"producer is not ready!"<<endl;
//            pthread_cond_wait(&cond, &mlock);
//            break;
//        }
//        cout<<"producer is ready..."<<endl;
//        pop_front(head, &data);
//        cout<<__func__<<" data is "<<data<<endl;
//
//        pthread_mutex_unlock(&mlock);
//        sleep(1);
//    }
//}
//
//void* producer(void *argv)
//{
//    int data=rand()%123;
//    while(1)
//    {
//        sleep(4);
//        pthread_mutex_lock(&mlock);
//        push_front(head,data);
//        cout<<__func__<<"data is "<<data<<endl;
//        pthread_mutex_unlock(&mlock);
//        pthread_cond_signal(&cond);
//    }
//}
//
//int main(int argc,char const *argv[])
//{
//    init(&head);
//    pthread_t id1,id2;
//    pthread_create(&id1, NULL, consumer, NULL);
//    pthread_create(&id2, NULL, producer, NULL);
//    pthread_join(id1,NULL);
//    pthread_join(id2,NULL);
//    return 0;
//}

//##############################
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

class Consumer:public Thread
{
public:
    void run()
    {

        int data=rand()%12;
        while(1)
        {
            sleep(4);
            pthread_mutex_lock(&mlock);
            push_front(head,data);
            cout<<__func__<<"data is "<<data<<endl;
            pthread_mutex_unlock(&mlock);
            pthread_cond_signal(&cond);
        }
    }
};

class Producer:public Thread
{
public:
    void run()
    {
        int data;
        while(1)
        {
            pthread_mutex_lock(&mlock);
            while(head->_next==NULL)
            {
                cout<<"producer is not ready!"<<endl;
                pthread_cond_wait(&cond, &mlock);
                break;
            }
            cout<<"producer is ready..."<<endl;
            pop_front(head, &data);
            cout<<__func__<<" data is "<<data<<endl;
            
            pthread_mutex_unlock(&mlock);
            sleep(1);
        }
    }
};

int main()
{
    init(&head);
    Consumer td1;
    Producer td2;
    td1.start();
    td2.start();
    td1.join();
    td2.join();
    //cout<<g_val<<endl;
    return 0;
}



