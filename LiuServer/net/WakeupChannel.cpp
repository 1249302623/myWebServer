#include"WakeupChannel.h"
#include"Util.h"
#include"Logging.h"
#include"EventLoop.h"
WakeupChannel::WakeupChannel(EventLoop* eventLoop,int fd)
    :Channel(eventLoop,fd)
{
    this->setEvents(EPOLLIN);//读事件，LT方式
}
void  WakeupChannel::handleRead(){
  uint32_t one = 1;
  ssize_t n = readLT(this->fd_, &one, sizeof one);
  if (n != sizeof one) {
    //LOG_FATAL<< "EventLoop::handleRead() reads " << n << " bytes instead of 8";
  }
  this->setEvents(EPOLLIN);
}
void WakeupChannel::handleConn(){
  this->eventLoop_->updatePoller(this);
}
