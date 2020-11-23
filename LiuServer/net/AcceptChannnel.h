#pragma once

#include"Channel.h"
class ConnThreadPool;
class EventLoop;
class AcceptChannel:public Channel{
private:
    ConnThreadPool* connThreadPool_;
public:
    AcceptChannel(EventLoop* eventLoop,ConnThreadPool* connThreadPool,int fd=0);
    void handleRead();
    void handleWrite(){}
    void handleConn();
    void handleError(int fd, int err_num, std::string short_msg){}
};