#include "ConnThreadPool.h"

ConnThreadPool::ConnThreadPool(EventLoop *baseLoop, int numThreads)
    : baseLoop_(baseLoop), 
      started_(false), 
      numThreads_(numThreads), 
      next_(0) {
  if (numThreads_ <= 0) {
    //LOG_ERROR<< "numThreads_ <= 0";
    abort();
  }
}

void ConnThreadPool::start() {
  baseLoop_->assertInLoopThread();
  started_ = true;
  for (int i = 0; i < numThreads_; ++i) {
    std::shared_ptr<ConnThread> t(new ConnThread());
    connThreads_.push_back(t);
    loops_.push_back(t->startLoop());
  }
}

EventLoop *ConnThreadPool::getNextLoop() {
  baseLoop_->assertInLoopThread();
  assert(started_);
  EventLoop *loop = baseLoop_;
  if (!loops_.empty()) {
    loop = loops_[next_];
    next_ = (next_ + 1) % numThreads_;
  }
  return loop;
}