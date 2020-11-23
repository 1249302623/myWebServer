// CountDownLatch的主要作用是确保Thread中传进去的func真的启动了以后
// 外层的start才返回
#pragma once
#include"Condition.h"
#include"MutexLock.h"
#include"noncopyable.h"
#include<memory>
class CountDownLatch{
public:
    explicit CountDownLatch(int count);
    void wait();
    void countdown();

private:
    //被mutable修饰的变量，将永远处于可变的状态 
    mutable MutexLock mutex_;
    Condition condition_;
    int count_;
};