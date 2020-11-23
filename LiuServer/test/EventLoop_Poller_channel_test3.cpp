#include "Channel.h"
#include "EventLoop.h"
#include"Logging.h"
#include <stdio.h>
#include <sys/timerfd.h>

EventLoop* g_loop;
class timeTestChannel:public Channel{
public:
    timeTestChannel(EventLoop* eventLoop):
    Channel(eventLoop,timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC))
    {
      struct itimerspec howlong;
      bzero(&howlong, sizeof howlong);
      howlong.it_value.tv_sec = 1;
      timerfd_settime(fd_, 0, &howlong, NULL);
      this->setEvents(EPOLLIN | EPOLLET);//读事件，ET方式
    }
    //void InitChannel();
    void handleRead(){
      this->timeout();
    }
    void handleWrite(){}
    void handleConn(){}
    void handleError(int fd, int err_num, std::string short_msg){}
    void timeout()
    {
      printf("Timeout!\n");
      g_loop->quit();
    }
};


int EventLoop_Poller_channel_test3_main()
{
  EventLoop loop;
  g_loop = &loop;
  
  Channel* channel_ptr=new timeTestChannel(&loop);
    //进程可以通过调用timerfd_create()创建特定的定时器
//     struct itimerspec {
//     struct timespec it_interval;  /*定时间隔周期*/
//     struct timespec it_value;     /* Initial expiration (第一次定时/到时/超时时间)*/
// };
   loop.addToPoller(channel_ptr);
  //loop.updateChannel(&channel);
// int timerfd_settime(int fd, int flags, const struct itimerspec *new_value, struct itimerspec *old_value)
// flags:      
//   	0 相对时间。  
//   	1 绝对时间(TFD_TIMER_ABSTIME)
// new_value: 
//    	定时器的超时时间以及超时间隔时间
// old_value: 
// 	如果不为NULL, old_vlaue返回之前定时器设置的超时时间，具体参考timerfd_gettime()函数
// 如果flags设置为1，那么epoll监听立马就有事件可读，并且读出的timerfd不是1，因为开机已经过去了很久。
// 如果设置为0，那么会按照设定的时间定第一个定时器，到时后读出的超时次数是1。
  
  loop.loop();
  //delete AsyncLogger_;
}
//int timerfd_create(int clockid, int flags)
// 1. clockid：
// CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,即从UTC1970-1-1 0:0:0  开始计时,中间时刻
// 				如果系统时间被用户改成其他,则对应的时间相应改变
// CLOCK_MONOTONIC:从系统启动这一刻起开始计时,不受系统时间被用户改变的影响
// 2. flags：
// TFD_NONBLOCK: 	非阻塞模式)     
// TFD_CLOEXEC:	表示当程序执行exec函数时本fd将被系统自动关闭,表示不传递
