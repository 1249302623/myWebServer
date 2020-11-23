#pragma once
#include<pthread.h>
#include"noncopyable.h"
#include<assert.h>
#include"CurrentThread.h"

class MutexLock:noncopyable{
public:
    explicit MutexLock(){
        hold_=0;
        pthread_mutex_init(&mutex,NULL);
    }
    ~MutexLock(){
        pthread_mutex_lock(&mutex);
        assert(hold_==0);       
        pthread_mutex_destroy(&mutex);
    }
      // 必须在lock操作前调用，用于断言
  // 防止同一线程对mutex重复加锁
  // 主要是防止嵌套加锁，例如在Queue的push函数中调用size()函数
    bool isLockedByThisThread(){
        return this->hold_==CurrentThread::tid();
    }
    // 断言已经被此线程占有，可用于在cond.wait()前进行断言
    void assertLocked(){
        assert(isLockedByThisThread());
    }
    void lock(){
        pthread_mutex_lock(&mutex);
        assignHolder();
        //hold_=CurrentThread::tid();
    }
    void unlock(){
        //hold_=0;
        unassignHolder();
        pthread_mutex_unlock(&mutex);    
    }
    pthread_mutex_t* getPthreadMutex(){
        return &mutex;
    }
    pthread_mutex_t* get(){
        return &mutex;
    }
private:
    friend class Condition;

    // 利用了RAII技术，构造时清空线程ID，析构时重新记录pid
    class UnassignGuard :noncopyable
    {
    public:
        UnassignGuard(MutexLock& owner)
        : owner_(owner)
        {
            owner_.unassignHolder();
        }

        ~UnassignGuard()
        {
            owner_.assignHolder();
        }

        private:
            MutexLock& owner_;
    };

    // 解锁时清空线程pid
    void unassignHolder()
    {
        hold_ = 0;
    }

    // 记录进行加锁的线程pid
    void assignHolder()
    {
        hold_ = CurrentThread::tid();
    }
private:
    pthread_mutex_t mutex;
    pid_t hold_;
};
class MutexLockGuard:noncopyable{
public:
    explicit MutexLockGuard(MutexLock &mutex)
    :mutex_(mutex){
        mutex_.lock();
    }
    ~MutexLockGuard(){
        mutex_.unlock();
    }
private:
    MutexLock &mutex_;
};