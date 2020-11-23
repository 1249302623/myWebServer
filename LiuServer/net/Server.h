#pragma once
#include <memory>
#include "Channel.h"
#include "EventLoop.h"

#include "ConnThreadPool.h"

class Server {
public:
  Server(EventLoop *loop, int connthreadNum, int port,int workthreadNum=3,int mysqlconnnum=5);
  ~Server() {
  }
  EventLoop *getLoop() const { return loop_; }
  void start();
  static const int MAXFDS = 160000;//只有静态常量整型才能在类中初始化
  
private:
  int port_;
  EventLoop *loop_;
  int connthreadNum_;
  int workthreadNum_;
  int mysqlconnnum_;
  std::unique_ptr<ConnThreadPool> connThreadPool_;
  bool started_;
  int listenFd_;
  Channel* acceptChannel_;

};