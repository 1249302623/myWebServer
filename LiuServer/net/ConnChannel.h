#pragma once
#include <sys/epoll.h>
#include <unistd.h>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include"Channel.h"
#include"MutexLock.h"
#include"Buffer.h"
#include"Logging.h"
#include"HttpData.h"
const int DEFAULT_EXPIRED_TIME =30*1000;         // ms
const int DEFAULT_KEEP_ALIVE_TIME =60 * 1000;  // ms
class EventLoop;
class TimerNode;
enum ConnectionState { H_CONNECTED = 0, H_DISCONNECTING, H_DISCONNECTED };
class ConnChannel : public Channel {
public:
  ConnChannel(EventLoop *loop, int connfd,std::string peerAddress);
  ~ConnChannel() { 
    //LOG_INFO<<"peer="<<this->peerAddress_<<" close";
  }
  void reset();
  void seperateTimer();
  void linkTimer(std::shared_ptr<TimerNode> mtimer) {
    timer_ = mtimer;
  }
  EventLoop *getLoop() { return this->eventLoop_; }
  void handleClose();
  void newEvent();
  Buffer& getinputBuffer(){
    return this->inputBuffer_;
  }
  Buffer& getoutputBuffer(){
    return this->outputBuffer_;
  }
  void handleRead();
  void handleWrite();//套接字一次传送的最大数据量应不会超过65536(2^16)，也就是６４ｋ左右
  void handleConn();
  void handleError(int fd, int err_num, std::string short_msg){}
  MutexLock& getinputBufferMutex(){ return inputBufferMutex_; }
  MutexLock& getoutputBufferMutex(){ return outputBufferMutex_; }
  void setkeepAlive(bool on){
    this->keepAlive_=on;
  }
  std::string getPeerAddress(){ return peerAddress_;}
  HttpData& getHttpData(){ return httpData_;}
  std::shared_ptr<TimerNode> getTimerNode(){ return timer_.lock(); }
private:
  
  std::string peerAddress_;
  Buffer inputBuffer_;
  Buffer outputBuffer_;
  bool error_;
  ConnectionState connectionState_;
  bool keepAlive_;
  //TimerNode* timer_;
  std::weak_ptr<TimerNode> timer_;
  MutexLock inputBufferMutex_;
  MutexLock outputBufferMutex_;
  HttpData httpData_;
};