#include <iostream>
#include<stdlib.h>
#include<thread>
#include<unistd.h>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<functional>
#include<queue>
#define N 3
using namespace std;
class ThreadPool{

public:
    //自定义void()的函数类型
    typedef function<void()>Task;

    ThreadPool();
    ~ThreadPool();

public:
    size_t initnum;
    //线程数组
    vector<thread>threads ;

    //任务队列
    queue<Task>task ;

    //互斥变量、条件变量
    mutex _mutex ;
    condition_variable cond ;

    //线程池工作结束时为真
    bool done ;

    //队列是否为空
    bool isEmpty ;
    //队列是否为满
    bool isFull;

public:
    void addTask(const Task&f);
    void create(int num);
    void setSize(int num);
    void runTask();
    void finish();
};

ThreadPool ::ThreadPool():done(false),isEmpty(true),isFull(false){
}

//设置池中初始线程数
void ThreadPool::setSize(int num){
        (*this).initnum = num ;
}

//添加任务
void ThreadPool::addTask(const Task&f){

    if(!done){
        
        unique_lock<mutex>lk(_mutex);

        while(isFull){
            cout<<"Task queue is full!"<<endl;
            cond.wait(lk);
        }

        task.push(f);

        if(task.size()==initnum)
            isFull = true;

        cout<<"A task is adding"<<endl;
        isEmpty = false ;
        cond.notify_one();
    }
}

void ThreadPool::finish(){
    for(size_t i =0 ;i<threads.size();i++){
           threads[i].join() ;
    }
}

void ThreadPool::runTask(){

    //不断遍历队列,判断要是有任务的话,就执行
    while(!done){

        unique_lock<mutex>lk(_mutex);

        //队列为空的话,就等待任务
        while(isEmpty){
            cout<<"Task queue is empty & waiting"<<endl;
            cond.wait(lk);
        }

        Task ta ;

        ta = move(task.front());
        task.pop();

        if(task.empty()){
            isEmpty = true ;
        }
        isFull =false ;
        lk.unlock();
        ta();
        cond.notify_one();
    }
}

void ThreadPool::create(int num){

    setSize(num);

    for(int i=0;i<num;i++){
        cout<<"创建第"<<i+1<<"个线程"<<endl;
        threads.push_back(thread(&ThreadPool::runTask,this));
    }
}
ThreadPool::~ThreadPool(){
}

int g_val=0;
void func(){
    for(int i=0;i<500000;++i)
    {
        int tmp=g_val;
        g_val=tmp+1;
    }
    cout<<"result is "<<g_val<<endl;
}
int main()
{
    ThreadPool p ;
    p.create(N);

    while(1){
        this_thread::sleep_for(chrono::seconds(1));
        auto task = func;
        p.addTask(task);
    }
    p.finish();
    return 0;
}


