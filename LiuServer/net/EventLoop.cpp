#include "EventLoop.h"
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <iostream>
#include "Util.h"
#include "Logging.h"
#include"WakeupChannel.h"
#include"Util.h"
#include<assert.h>
__thread EventLoop* t_loopInThisThread = 0;

int createEventfd() {
  int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  if (evtfd < 0) {
    //LOG_ERROR<< "Failed in eventfd";
    abort();
  }
  return evtfd;
}

EventLoop::EventLoop()
    : looping_(false),
      poller_(new Epoll()),
      wakeupFd_(createEventfd()),
      quit_(false),
      eventHandling_(false),
      callingPendingFunctors_(false),
      threadId_(CurrentThread::tid()),
      pwakeupChannel_(new WakeupChannel(this,wakeupFd_)) {
  if (t_loopInThisThread) {
    //LOG_ERROR<< "Another EventLoop  exists in this thread " << threadId_;
  } 
  else {
    t_loopInThisThread = this;
  }
  poller_->epoll_add(pwakeupChannel_,0);
}
EventLoop::~EventLoop() {
  close(wakeupFd_);
  delete poller_;
  poller_=NULL;
  pwakeupChannel_=NULL;
  t_loopInThisThread = NULL;
}

void EventLoop::wakeup() {
  uint64_t one = 1;
  ssize_t n = writeLT(wakeupFd_, (char*)(&one), sizeof one);
  if (n != sizeof one) {
    //LOG << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
  }
}

void EventLoop::runInLoop(const std::function<void()>& cb) {
  if (isInLoopThread())
    cb();
  else
    queueInLoop(cb);
}
   // 调用queueInLoop的线程不是IO线程需要唤醒
  // 或者调用queueInLoop的线程是IO线程，并且此时正在调用pending functor，需要唤醒
  // 只有IO线程的事件回调中调用queueInLoop才不需要唤醒
void EventLoop::queueInLoop(const std::function<void()>& cb) {
  {
    MutexLockGuard lock(mutex_);
    pendingFunctors_.emplace_back(cb);
    //emplace_back() 和 push_back() 的区别，就在于底层实现的机制不同。
    //push_back() 向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中
    //（如果是拷贝的话，事后会自行销毁先前创建的这个元素）；
    //而 emplace_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。
  }
  if (!isInLoopThread() || callingPendingFunctors_) 
    wakeup();
}

void EventLoop::loop() {
  assert(!looping_);
  assert(isInLoopThread());
  looping_ = true;
  quit_ = false;
  //LOG_TRACE << "EventLoop " << this << " start looping";
  std::vector<Channel*> ret;
  while (!quit_) {
    ret.clear();
    ret = poller_->poll();
    eventHandling_ = true;
    for (auto& it : ret) it->handleEvents();
    eventHandling_ = false;
    doPendingFunctors();
    poller_->handleExpired();
  }
  looping_ = false;
}

void EventLoop::doPendingFunctors() {
  std::vector<std::function<void()> > functors;
  callingPendingFunctors_ = true;
  {
    MutexLockGuard lock(mutex_);
    functors.swap(pendingFunctors_);//将共享变量pendingFunctors_置入functors，后将其置0，
  }
  for (size_t i = 0; i < functors.size(); ++i) {
    functors[i]();
  }
  callingPendingFunctors_ = false;
}

void EventLoop::quit() {
  quit_ = true;
  if (!isInLoopThread()) {
    wakeup();
  }
}