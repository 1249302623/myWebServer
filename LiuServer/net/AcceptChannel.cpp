#include"AcceptChannnel.h"
#include"Util.h"
#include"Logging.h"
#include"EventLoop.h"
#include <arpa/inet.h>
#include"Server.h"
#include"ConnChannel.h"
#include"ConnThreadPool.h"
//const int DEFAULT_EXPIRED_TIME = 2000;              // ms
AcceptChannel::AcceptChannel(EventLoop* eventLoop,ConnThreadPool* connThreadPool,int fd)
    :Channel(eventLoop,fd),connThreadPool_(connThreadPool)
{
    this->setEvents(EPOLLIN | EPOLLET);//读事件，ET方式
}
// 接受一个TCP连接
/*  listen函数指定的监听socket   addr   请求连接方（即客户端）地址   addrlen 客户端地址长度
  * return 函数执行成功返回一个新的连接socket，失败返回-1  它将返回一个新的套接字文件描述符！这样你就有两个套接字了，
  * 原来的一个还在侦听你的那个端口，的在准备发送send()和接收 recv()数据  */
void  AcceptChannel::handleRead(){
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    socklen_t client_addr_len = sizeof(client_addr);
    int accept_fd = 0;
    while ((accept_fd = accept(this->getFd(), (struct sockaddr *)&client_addr,
                             &client_addr_len)) > 0)
    {
      EventLoop *loop = connThreadPool_->getNextLoop();
      //inet_ntoa函数能把网络字节序IP转化点分十进制IP
      std::string peerAddress=std::string(inet_ntoa(client_addr.sin_addr))
        +std::string(":")+std::to_string(ntohs(client_addr.sin_port));
      //LOG_INFO<< "New connection from " << peerAddress;
      // 限制服务器的最大并发连接数
      if (accept_fd >=Server::MAXFDS) {
        LOG_INFO<< "New connection too big " << peerAddress;
        close(accept_fd);
        continue;
      }
      // 设为非阻塞模式
      if (setSocketNonBlocking(accept_fd) < 0) {
        LOG_WARN<< "Set non block failed!";
        // perror("Set non block failed!");
        return;
      }
      setSocketNodelay(accept_fd);
      Channel* req_info(new ConnChannel(loop, accept_fd,peerAddress));
      //req_info->setEvents(EPOLLIN | EPOLLONESHOT);
      // loop->runInLoop(std::bind(&EventLoop::updatePoller,
      //     loop,req_info,DEFAULT_EXPIRED_TIME));
      //loop->addToPoller(req_info,DEFAULT_EXPIRED_TIME);
    }
    this->setEvents(EPOLLIN | EPOLLET);
    //printf("newConnection(): accepted a new connection from \n");
}

void AcceptChannel::handleConn(){
  eventLoop_->updatePoller(this);
}