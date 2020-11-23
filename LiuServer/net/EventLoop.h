#pragma once
#include <functional>
#include <memory>
#include <vector>
#include "Channel.h"
#include "Epoll.h"
#include "CurrentThread.h"
#include "Logging.h"
#include"MutexLock.h"
#include"Timestamp.h"
#include"Util.h"
#include <iostream>

class EventLoop{
public:
  EventLoop();
  ~EventLoop();
  void loop();
  void quit();
  void runInLoop(const std::function<void()>& cb);
  void queueInLoop(const std::function<void()>& cb);
  bool isInLoopThread() const { return threadId_== CurrentThread::tid(); }
  void assertInLoopThread() { assert(isInLoopThread()); }
  void shutdown(Channel* channel) { shutDownWR(channel->getFd()); }
  void removeFromPoller(Channel* channel) {
    poller_->epoll_del(channel);
  }
  void updatePoller(Channel* channel,int timeout = 0) {
    poller_->epoll_mod(channel,timeout);
  }
  void addToPoller(Channel* channel,int timeout = 0) {
    poller_->epoll_add(channel,timeout);
  }
  bool eventHandling() const { return eventHandling_; }
  void wakeup();
private:
  // 声明顺序 wakeupFd_ > pwakeupChannel_
  bool looping_;
  Epoll* poller_;
  int wakeupFd_;
  bool quit_;
  bool eventHandling_;
  mutable MutexLock mutex_;
  std::vector<std::function<void()>> pendingFunctors_;
  bool callingPendingFunctors_;
  const pid_t threadId_;
  Channel* pwakeupChannel_;
  Timestamp pollReturnTime_;
  void doPendingFunctors();
};
