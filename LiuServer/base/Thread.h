#pragma once
#include"noncopyable.h"
#include"CountDownLatch.h"
#include"Atomic.h"
#include<thread>
#include<memory>
class Thread:noncopyable{
protected:
    void setDefaultName();
    bool started_;
    bool join_ed;
    pthread_t pthreadId_;
    pid_t tid_;
   //我们在线程对象析构之前，必须调用join或者detach,基于这个考虑的原因是
   //如果thread不调用join或者detach那么句柄信息得不到关闭导致内存泄露。
    std::unique_ptr<std::thread> std_thread_ptr;
    std::string name_;
    CountDownLatch latch_;
public:
    virtual void runInThisThread()=0;
    explicit Thread(const std::string& name=std::string());
    virtual ~Thread();
    void join();
    bool started() const{ return started_;}
    pid_t tid() const {return tid_;}
    const std::string& name() const{return name_;}
    static AtomicInt32 numCreated_;
    static int numCreated() { return numCreated_.get(); }
    void start();
    void startInNewThread();
};
