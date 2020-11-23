#pragma once
#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Channel.h"
//epoll是linux2.6内核的一个新的系统调用，
//epoll在设计之初，就是为了替代select, poll线性复杂度的模型，
//epoll的时间复杂度为O(1), 也就意味着，epoll在高并发场景，随着文件描述符的增长，有良好的可扩展性。
///proc/sys/fs/epoll/max_user_watches
//表示用户能注册到epoll实例中的最大文件描述符的数量限制。
//本机为400670
class TimerManager;
class Epoll {
public:
  Epoll();
  ~Epoll();
  void epoll_add(Channel* request,int timeout);
  void epoll_mod(Channel* request,int timeout);
  void epoll_del(Channel* request);
  std::vector<Channel*> poll();
  std::vector<Channel*> getEventsRequest(int events_num);
  void add_timer(Channel* request_data, int timeout);
  int getEpollFd() { return epollFd_; }
  void handleExpired();

private:
  static const int MAXFDS = 160000;//linux虚拟机系统全部能够打开的fd总数为194570
  int epollFd_;
  std::vector<epoll_event> events_;
  Channel* fdMap[MAXFDS];
  std::shared_ptr<TimerManager> timerManager_;
};