#include "ConnThread.h"
#include <functional>

ConnThread::ConnThread()
    : loop_(NULL),
      mutex_(),
      cond_(mutex_),
      Thread("ConnThread") 
{}

ConnThread::~ConnThread() {
  if (loop_ != NULL) {
    loop_->quit();
    this->join();
    delete loop_;
  }
}

EventLoop* ConnThread::startLoop() {
  assert(!this->started());
  this->start();
  {
    MutexLockGuard lock(mutex_);
    // 一直等到runInThisThread在Thread里真正跑起来
    while (loop_ == NULL) {
      cond_.wait();
    }
  }
  return loop_;
}

void ConnThread::runInThisThread() {
  EventLoop* loop=new EventLoop();
  {
    MutexLockGuard lock(mutex_);
    loop_ =loop;
    cond_.notify();
  }
  loop_->loop();
  delete loop_;
  loop_ = NULL;
}