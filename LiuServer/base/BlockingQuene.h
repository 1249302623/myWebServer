#pragma once
//yes
#include"noncopyable.h"
#include"MutexLock.h"
#include"Condition.h"
#include<queue>
template<class T>
class BlockingQuene:noncopyable{
public:
    BlockingQuene()
        :mutex_(),
         notEmpty_(mutex_),
         quene_()
    {    
    }
    void put(const T& x){
        MutexLockGuard lock(mutex_);
        quene_.push_back(x);
        notEmpty_.notify();
    }
    T take(){
        MutexLockGuard lock(mutex_);
        while (quene_.empty())
        {
            notEmpty_.wait();
        }
        assert(!quene_.empty());
        T front(quene_.front());
        quene_.pop_front();
        return front;
    }
    bool empty(){
        return quene_.empty();
    }

    size_t size() const{
        MutexLockGuard lock(mutex_);
        return quene_.size();
    }
private:
    mutable MutexLock mutex_;
    Condition notEmpty_;
    std::deque<T> quene_;
};