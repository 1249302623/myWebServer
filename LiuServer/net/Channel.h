#pragma once
#include <sys/epoll.h>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include"unistd.h"
#include"Logging.h"
class EventLoop;
class Channel {
protected:
  int fd_;
  __uint32_t events_;
  __uint32_t revents_;
  __uint32_t lastEvents_;
  EventLoop* eventLoop_;
public:
  Channel(EventLoop* eventLoop,int fd=0)
    :events_(0),lastEvents_(0),fd_(fd),eventLoop_(eventLoop){}
  virtual ~Channel(){
    close(fd_);
    //LOG_INFO<<"fd="<<this->getFd()<<"  close";
  }
  int getFd(){
    return this->fd_;
  }
  void setFd(int fd){
    this->fd_=fd;
  }
  EventLoop* getloop(){return this->eventLoop_;}
  void handleEvents() {
    events_ = 0;
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
      events_ = 0;
      return;
    }
    if (revents_ & EPOLLERR) {  // 错误事件处理
      events_ = 0;
      //handleError  后面要补上
      return;
    }
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {//有数据可读
      handleRead();
      //在非阻塞网络编程中，accept的描述符可读，表明有新的连接上来
      //connection 描述符可读，表示连接收到了客户端的数据
    }
    if (revents_ & EPOLLOUT) {
      handleWrite();
    }
    handleConn();
  }
  virtual void handleRead()=0;
  virtual void handleWrite()=0;
  virtual void handleError(int fd, int err_num, std::string short_msg)=0;
  virtual void handleConn()=0;
  //virtual void InitChannel()=0;

  void setRevents(__uint32_t ev) { revents_ = ev; }

  void setEvents(__uint32_t ev) { events_ = ev; }

  __uint32_t &getEvents() { return events_; }

  bool EqualAndUpdateLastEvents() {
    bool ret = (lastEvents_ == events_);
    lastEvents_ = events_;
    return ret;
  }

  __uint32_t getLastEvents() { return lastEvents_; }
};
