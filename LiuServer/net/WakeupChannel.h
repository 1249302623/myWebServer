#pragma once
#include"Channel.h"
#include<memory>

class EventLoop;
class WakeupChannel:public Channel{

public:
    WakeupChannel(EventLoop* eventLoop,int fd=0);
    void handleRead();
    void handleWrite(){}
    void handleConn();
    void handleError(int fd, int err_num, std::string short_msg){}
};