#pragma once
#include"noncopyable.h"
#include"MutexLock.h"
#include<pthread.h>
#include<cstdint>
#include<time.h>
#include<errno.h>
class Condition{
private:
    MutexLock &mutex_;
    pthread_cond_t cond;
public:
    explicit Condition(MutexLock& _mutex):mutex_(_mutex){
        pthread_cond_init(&cond,NULL);
    }
    ~Condition(){
        pthread_cond_destroy(&cond);
    }

    void wait(){
        //MutexLock::UnassignGuard ug(mutex_);
        pthread_cond_wait(&cond,mutex_.get());
    }
    void notify(){
        pthread_cond_signal(&cond);
    }
    void notifyall(){
        pthread_cond_broadcast(&cond);
    }
    bool waitForSecond(int seconds){
        struct timespec abstime;
        abstime.tv_sec+=static_cast<time_t>(seconds);
        return ETIMEDOUT ==
            pthread_cond_timedwait(&cond,mutex_.get(),&abstime);
        //比函数pthread_cond_wait()多了一个时间参数，经历abstime段时间后，即使条件变量不满足，阻塞也被解除。
        //计时等待方式如果在给定时刻前条件没有满足，则返回ETIMEOUT，结束等待
    }

};