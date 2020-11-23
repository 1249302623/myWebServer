#include "ConnChannel.h"
#include"Logging.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <iostream>
#include "EventLoop.h"
#include "Util.h"
#include <time.h>
#include <iostream>
#include"Timer.h"
#include"Singleton.h"
#include"WorkThreadPool.h"


ConnChannel::ConnChannel(EventLoop *loop, int connfd,std::string peerAddress)
    :Channel(loop, connfd),
      error_(false),
      connectionState_(H_CONNECTED),
      keepAlive_(false) ,
      peerAddress_(peerAddress),
      httpData_(this),
      inputBufferMutex_(),
      outputBufferMutex_()
{
  setEvents(EPOLLIN | EPOLLONESHOT);
  loop->runInLoop(std::bind(&EventLoop::addToPoller,loop,this,DEFAULT_EXPIRED_TIME));
  //loop->addToPoller(this,DEFAULT_EXPIRED_TIME);
}

void ConnChannel::reset() {
  // if (timer_!=NULL) {
  //   timer_->clearReq();
  //   timer_=NULL;
  // }
}
void ConnChannel::seperateTimer() {
  // if (timer_!=NULL) {
  //   timer_->clearReq();
  //   timer_=NULL;
  // }
  if (timer_.lock()) {
    std::shared_ptr<TimerNode> my_timer(timer_.lock());
    my_timer->clearReq();
    timer_.reset();
  }
}
void ConnChannel::handleRead() {
    eventLoop_->assertInLoopThread();
    ssize_t n;
    {
    MutexLockGuard lock(this->inputBufferMutex_);
    n = inputBuffer_.readFd(this->getFd());
    }
    //LOG_INFO<<"connThread success recive from  "<<getPeerAddress();
    if (n > 0)
    {
      Singleton<WorkThreadPool>::instance().getRead(this);
      events_ |= EPOLLIN;
    }
    else if (n == 0)
    {
        //读不到数，表明对面发送了一个关闭信号，此时我要发送完成我的buffer再将其关闭
        //printf("client close\n");
        connectionState_ = H_DISCONNECTING;
      //以下为测试
      // events_ |= EPOLLOUT;//要发送
      // this->outputBuffer_.append("hello I want to close");
    }
    else
    {
        //LOG_SYSERR << "TcpConnection::handleRead failed";
    }
}

void ConnChannel::handleWrite() {
  if(connectionState_!=H_DISCONNECTED){
    ssize_t n;
    eventLoop_->assertInLoopThread();
    {
    MutexLockGuard lock(getoutputBufferMutex());
    n =writeLT(this->fd_,
                    outputBuffer_.peek(),
                    outputBuffer_.readableBytes());
    //_INFO<<"success send to"<<getPeerAddress()<<"length="<<n ;
    }
   
    if (n > 0)
    {
      outputBuffer_.retrieve(n); // 从输出缓冲区中将已经发送的数据移除
      if (outputBuffer_.readableBytes() == 0) { 
        events_ |= (EPOLLIN);
      }// 所有数据已经发送完毕
      else{
        //LOG_SYSERR << "TcpConnection::handleWrite";
        events_ |= EPOLLOUT;//还要再次发送
      }
    }
    else{
      //LOG_TRACE << "Connection fd = " <<this->fd_<< " is down, no more writing";
    }
  }
}

void ConnChannel::handleConn() {
  seperateTimer();
  __uint32_t &events_ = this->getEvents();
  if (connectionState_ == H_CONNECTED) {
    if (events_ != 0) {
      int timeout = DEFAULT_EXPIRED_TIME;
      if (keepAlive_) 
        timeout = DEFAULT_KEEP_ALIVE_TIME;
      if ((events_ & EPOLLIN) && (events_ & EPOLLOUT)) {//如果有读有写，那么只进行写
        events_ = __uint32_t(0);
        events_ |= EPOLLOUT;
      }
      eventLoop_->updatePoller(this,timeout);
    } 
    else if (keepAlive_) {    //如果已经写完，则开始读
      events_ |= (EPOLLIN);
      int timeout = DEFAULT_KEEP_ALIVE_TIME;
       eventLoop_->updatePoller(this,timeout);
    } 
    else {   //如果已经写完，则开始读
      events_ |= (EPOLLIN);

      int timeout =DEFAULT_EXPIRED_TIME;
      eventLoop_->updatePoller(this,timeout);
    }
  } 
  else if (connectionState_ == H_DISCONNECTING && (events_ & EPOLLOUT))//如果正在关闭而且需要写
  {
    events_ = (EPOLLOUT);
  } 
  else {             //如果正在关闭且不需要写或已关闭
    eventLoop_->assertInLoopThread();
    handleClose();
  }
}
void ConnChannel::handleClose() {
  seperateTimer();
  connectionState_ = H_DISCONNECTED;
  eventLoop_->removeFromPoller(this);
}
//* 对于client(非Keep-Alive)，发送完请求后就可以shutdown()写端，然后收到server发来的应答，
//最后close掉连接。也可以不shutdown()写，等读完直接close。
//对于Keep-Alive的情况，就要看client的心情了，收到消息后可以断，也可以不断，server应该保证不主动断开。

//##### EPOLLIN触发但是read()返回0的情况
//这种情况通常有两个原因:
//> * 对端已经关闭了连接，这时再写该fd会出错，此时应该关闭连接
//> * 对端只是shutdown()了写端，告诉server我已经写完了，但是还可以接收信息。server应该在写完所有的信息后再关闭连接。
//更优雅的做法是透明的传递这个行为，即server顺着关闭读端，然后发完数据后关闭。