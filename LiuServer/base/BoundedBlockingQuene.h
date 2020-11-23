#pragma once
#include"noncopyable.h"
#include"MutexLock.h"
#include"Condition.h"
#include<queue>

//有界队列
template<class T>
class BoundedBlockingQuene:noncopyable{
public:
    explicit BoundedBlockingQuene(int maxSize)
        :mutex_(),
         notEmpty_(mutex_),
         notFull_(mutex_),
         quene_(),
         max_(maxSize)
    {
    }
    void put(const T& x){
        MutexLockGuard lock(mutex_);
        while (this->quene_.size()>=max_)
        {
            notFull_.wait();
        }
        assert(this->quene_.size()<max_);
        quene_.push(x);
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
        quene_.pop();
        notFull_.notify();
        return front;
    }
    bool empty() const
    {
        MutexLockGuard lock(mutex_);
        return quene_.empty();
    }

    bool full() const
    {
        MutexLockGuard lock(mutex_);
        return quene_.size()>=max_;
    }

    size_t size() const
    {
        MutexLockGuard lock(mutex_);
        return quene_.size();
    }

    size_t capacity() const//容量
    {
        MutexLockGuard lock(mutex_);
        return max_;
    }
private:
    mutable MutexLock mutex_;
    Condition notEmpty_;
    Condition notFull_;
    std::queue<T> quene_;
    int max_;
};