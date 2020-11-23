#include"ThreadPool.h"
#include<stdio.h>
#include<assert.h>
#include<algorithm> 
#include<exception>
ThreadPool::ThreadPool(const std::string& name)
    :mutex_(),
     cond_(mutex_),
     name_(name),
     running_(false),
     quene_()
{    
}//初始化了互斥锁和条件变量，线程池名和运行标记。
//一个线程池的单例
ThreadPool::~ThreadPool(){
    if(running_){
        stop();
    }
}
//该函数传入参数为线程池创建线程的数量，也就是说该线程池中的线程在线程池创建后就确定了，无法修改。在函数内部首先判断线程数组是否为空，
void ThreadPool::start(int numThreads){
    assert(threads_.empty());
    running_=true;
    threads_.reserve(numThreads);
    for(int i=0;i<numThreads;i++){
        char id[32];
        snprintf(id,sizeof id,"%d",i);
        std::shared_ptr<ThreadPoolThread> s(new ThreadPoolThread (name_+id));
        threads_.push_back(s);
        threads_[i]->start();
    }
}
void ThreadPool::stop(){
    {
    MutexLockGuard lock(mutex_);
    running_=false;
    cond_.notifyall();
    }
    for(std::vector<std::shared_ptr<ThreadPoolThread>>::iterator it=threads_.begin();it!=threads_.end();it++){
        (*it)->join();
    }
}

//run函数接受一个Task任务作为参数传入，然后判断线程数组是否为空，如果为空，那么久直接执行该任务，否则将该任务送入任务队列中，然后唤醒等待函数ThreadPool::take()。上面分析到ThreadPool::take函数如果没有任务执行将一直处于等待状态。
//所以总结就是：void run(const Task& f)类似于“生产者”，生产线程，而ThreadPool::Task ThreadPool::take()则是“消费者”的角色，负责消费（取出）线程。
void ThreadPool::run(const Task& task){
    if(threads_.empty()){
        task();
    }
    else{
        MutexLockGuard lock(mutex_);
        quene_.push(task);
        cond_.notify();
    }
}
//该函数使用了互斥锁，一进入该函数就锁住，然后判断任务队列中是否有执行的任务以及是否线程池在运行，如果不满足条件，则通过条件变量等待，很明显，这里一开始是没有任务的，任务队列为空；当然，如果条件满足，如果任务队列不为空就将任务队列的第一个任务取出返回。
ThreadPool::Task ThreadPool::take(){
    MutexLockGuard lock(mutex_);
    while(quene_.empty()&&running_){
        cond_.wait();
    }
    Task task;
    if(!quene_.empty()){
        task=quene_.front();
        quene_.pop();
    }
    return task;
}

void ThreadPoolThread::runInThisThread(){
    while (Singleton<ThreadPool>::instance().running()){
        ThreadPool::Task task(Singleton< ThreadPool >::instance().take());
        if (task){
            task();
        }
    }
}