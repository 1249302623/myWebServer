#include "Epoll.h"
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <deque>
#include <queue>
//#include "Util.h"
#include "Logging.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include"ConnChannel.h"
#include"Timer.h"
const int EVENTSNUM = 4096;//活跃事件的最大容量4096
const int EPOLLWAIT_TIME = 2000;//10s 单位ms

Epoll::Epoll() 
  : 
  epollFd_(epoll_create1(EPOLL_CLOEXEC)), 
  events_(EVENTSNUM),
  timerManager_(new TimerManager()) 
{
  assert(epollFd_ > 0);
}
Epoll::~Epoll() {
  close(epollFd_);
  for(Channel* fdChannel:fdMap){
    if(fdChannel!=NULL){
       printf("fd=%d",fdChannel->getFd());
       delete fdChannel;
    }
    fdChannel=NULL;
  }
}
//  int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
// epoll的事件注册函数，epoll_ctl向 epoll对象中添加、修改或者删除感兴趣的事件，返回0表示成功，否则返回–1，此时需要根据errno错误码判断错误类型。
// 它不同与select()是在监听事件时告诉内核要监听什么类型的事件，而是在这里先注册要监听的事件类型。
// epoll_wait方法返回的事件必然是通过 epoll_ctl添加到 epoll中的。
// 第一个参数是epoll_create()的返回值，第二个参数表示动作，用三个宏来表示：
// EPOLL_CTL_ADD：注册新的fd到epfd中；
// EPOLL_CTL_MOD：修改已经注册的fd的监听事件；
// EPOLL_CTL_DEL：从epfd中删除一个fd；
// 第三个参数是需要监听的fd，第四个参数是告诉内核需要监听什么事
// 注册新描述符
void Epoll::epoll_add(Channel* request,int timeout) {
  int fd = request->getFd();
  if (timeout > 0) {
    add_timer(request, timeout);
  }
  struct epoll_event event;
  event.data.fd = fd;
  event.events = request->getEvents();//EPOLLET:设置关联的fd为ET的工作方式，epoll的默认工作方式是LT。

  request->EqualAndUpdateLastEvents();
  fdMap[fd]=request;
  if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &event) < 0) {
    perror("epoll_add error");
    //LOG_ERROR<<"epoll_add error in epollFd_="<<epollFd_;
    delete fdMap[fd];
    fdMap[fd]=NULL;
  }
}

// 修改描述符状态
void Epoll::epoll_mod(Channel* request,int timeout) {
  if (timeout > 0) add_timer(request, timeout);
  int fd = request->getFd();
  if (!request->EqualAndUpdateLastEvents()) {
    struct epoll_event event;
    event.data.fd = fd;
    event.events = request->getEvents();
    if (epoll_ctl(epollFd_, EPOLL_CTL_MOD, fd, &event) < 0) {
      perror("epoll_mod error");
      //LOG_ERROR<<"epoll_mod error in epollFd_="<<epollFd_;
      delete fdMap[fd];
      fdMap[fd]=NULL;
    }
  }
}

// 从epoll中删除描述符
void Epoll::epoll_del(Channel* request) {
  int fd = request->getFd();
  struct epoll_event event;
  event.data.fd = fd;
  event.events = request->getLastEvents();
  if (epoll_ctl(epollFd_, EPOLL_CTL_DEL, fd, &event) < 0) {
    perror("epoll_del error");
    //LOG_ERROR<<"epoll_del error in epollFd_="<<epollFd_;
  }
  if(fdMap[fd]){
    delete fdMap[fd];
    fdMap[fd]=NULL;
  }
}

// 返回活跃事件数
std::vector<Channel*> Epoll::poll() {
  while (true) {
    int event_count =
        epoll_wait(epollFd_, &*events_.begin(), events_.size(), EPOLLWAIT_TIME);
    if (event_count < 0){
      perror("epoll wait error");
      //LOG_ERROR<<"epoll wait error in epollFd_="<<epollFd_;
    }
    std::vector<Channel*> req_data = getEventsRequest(event_count);
    if (req_data.size() > 0) 
      return req_data;
    if(req_data.size()==0)
      this->handleExpired();
  }
}

void Epoll::handleExpired() 
{ 
  timerManager_->handleExpiredEvent(); 
}

// 分发处理函数
// 3. int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);
// 等待事件的产生，类似于select()调用。参数events用来从内核得到事件的集合，maxevents告之内核这个events有多大，
//这个 maxevents的值不能大于创建epoll_create()时的size，参数timeout是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）。
//该函数返回需要处理的事件数目，如返回0表示已超时。
//如果返回–1，则表示出现错误，需要检查 errno错误码判断错误类型。
// 第1个参数 epfd是 epoll的描述符。
// 第2个参数 events则是分配好的 epoll_event结构体数组，epoll将会把发生的事件复制到 events数组中（events不可以是空指针，内核只负责把数据复制到这个 events数组中，不会去帮助我们在用户态中分配内存。内核这种做法效率很高）。
// 第3个参数 maxevents表示本次可以返回的最大事件数目，通常 maxevents参数与预分配的events数组的大小是相等的。
// 第4个参数 timeout表示在没有检测到事件发生时最多等待的时间（单位为毫秒），如果 timeout为0，则表示 epoll_wait在 rdllist链表中为空，立刻返回，不会等待。
std::vector<Channel*> Epoll::getEventsRequest(int events_num) {
  std::vector<Channel*> req_data;
  for (int i = 0; i < events_num; ++i) {
    // 获取有事件产生的描述符
    int fd = events_[i].data.fd;

    Channel* cur_req = fdMap[fd];

    if (cur_req) {
      cur_req->setRevents(events_[i].events);
      cur_req->setEvents(0);
      req_data.push_back(cur_req);
    } 
    else {
      //LOG_WARN<< "std::shared_ptr<Channel> cur_req is invalid";
    }
  }
  return req_data;
}

void Epoll::add_timer(Channel* request_data, int timeout) {
  ConnChannel* request_data_copy=static_cast<ConnChannel*> (request_data);
  if(request_data_copy->getTimerNode()!=NULL)
    request_data_copy->seperateTimer();
  if(request_data)
    timerManager_->addTimer(
      static_cast<ConnChannel*> (request_data), timeout);
  else
  {
    //LOG_SYSERR<<"timer add fail";
  }
}