#pragma once
#include "EventLoop.h"
#include "Condition.h"
#include "MutexLock.h"
#include "Thread.h"
#include "noncopyable.h"

class ConnThread :public Thread 
{
public:
  ConnThread();
  ~ConnThread();
  EventLoop* startLoop();

private:
  void runInThisThread();
  EventLoop* loop_;
  MutexLock mutex_;
  Condition cond_;
};