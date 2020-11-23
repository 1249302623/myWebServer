#pragma once

#include"noncopyable.h"
#include<vector>
#include<queue>
#include<functional>
#include<string>
#include"MutexLock.h"
#include"Condition.h"
#include"Thread.h"
#include<memory>
#include"BlockingQuene.h"
#include"Singleton.h"

class ThreadPoolThread:public Thread{
    public:
        ThreadPoolThread(std::string name="ThreadPool")
            :Thread(name)
        {
        }
        void runInThisThread();

};
class ThreadPool:noncopyable{  //线程池是一个单例模式
public:
    typedef std::function<void()> Task;
    explicit ThreadPool(const std::string& name=std::string());
    ~ThreadPool();
    void start(int numThreads);
    void stop();
    void run(const Task& f);
    Task take();
    bool running(){
        return running_;
    }
private: 
    mutable MutexLock mutex_;
    Condition cond_;
    std::string name_;
    std::vector<std::shared_ptr<ThreadPoolThread>> threads_;
    bool running_;
    std::queue<Task> quene_;//deque 即双端队列,是一个共享队列
};

