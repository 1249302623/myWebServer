// @Author Lin Ya
// @Email xxbbb@vip.qq.com
#include "Util.h"
#include"Buffer.h"
const int MAX_BUFF = 4096;
ssize_t readLT(int sockfd, void *buf, size_t count)
{
  return ::read(sockfd, buf, count);
}
// 这里的iov是一个struct iovec的数组指针，可以将一系列分散的缓冲区中的值只通过一次系统调用全部读出来，如果要用read，就需要很多次
// readv与read不同之处在于，接收的数据可以填充到多个缓冲区中
ssize_t readvLT(int sockfd, const struct iovec *iov, int iovcnt)
{
  return ::readv(sockfd, iov, iovcnt);
}

ssize_t writeLT(int sockfd, const void *buf, size_t count)
{
  return ::write(sockfd, buf, count);
}

ssize_t readET(int fd, void *buff, size_t n) {
  size_t nleft = n;
  ssize_t nread = 0;
  ssize_t readSum = 0;
  char *ptr = (char *)buff;
  while (nleft > 0) {
    if ((nread = read(fd, ptr, nleft)) < 0) {
      if (errno == EINTR)
        nread = 0;
      else if (errno == EAGAIN) {
        return readSum;
      } else {
        return -1;
      }
    } else if (nread == 0)
      break;
    readSum += nread;
    nleft -= nread;
    ptr += nread;
  }
  return readSum;
}

ssize_t readET(int fd, std::string &inBuffer, bool &zero) {
  ssize_t nread = 0;
  ssize_t readSum = 0;
  while (true) {
    char buff[MAX_BUFF];
    if ((nread = read(fd, buff, MAX_BUFF)) < 0) {
      if (errno == EINTR)
        continue;
      else if (errno == EAGAIN) {
        return readSum;
      } else {
        perror("read error");
        return -1;
      }
    } else if (nread == 0) {
      // printf("redsum = %d\n", readSum);
      zero = true;
      break;
    }
    readSum += nread;
    inBuffer += std::string(buff, buff + nread);
  }
  return readSum;
}

ssize_t readET(int fd, std::string &inBuffer) {
  ssize_t nread = 0;
  ssize_t readSum = 0;
  while (true) {
    char buff[MAX_BUFF];
    if ((nread = read(fd, buff, MAX_BUFF)) < 0) {
      if (errno == EINTR)
        continue;
      else if (errno == EAGAIN) {//缓冲区被填满,需要再读一次
        return readSum;
      } 
      else {
        perror("read error");
        return -1;
      }
    } 
    else if (nread == 0) {
      break;
    }
    readSum += nread;
    inBuffer += std::string(buff, buff + nread);
  }
  return readSum;
}
//当碰到EINTR错误的时候，有一些可以重启的系统调用要进行重启，而对于有一些系统调用是不能够重启的。
//例如：accept、read、write、select、和open之类的函数来说，是可以进行重启的。


ssize_t writeET(int fd, void *buff, size_t n) {
  size_t nleft = n;
  ssize_t nwritten = 0;
  ssize_t writeSum = 0;
  char *ptr = (char *)buff;
  while (nleft > 0) {
    if ((nwritten = write(fd, ptr, nleft)) <= 0) {
      if (nwritten < 0) {
        if (errno == EINTR) {
          nwritten = 0;
          continue;
        } else if (errno == EAGAIN) {
          return writeSum;
        } else
          return -1;
      }
    }
    writeSum += nwritten;
    nleft -= nwritten;
    ptr += nwritten;
  }
  return writeSum;
}

ssize_t writeET(int fd, std::string &sbuff) {
  size_t nleft = sbuff.size();
  ssize_t nwritten = 0;
  ssize_t writeSum = 0;
  const char *ptr = sbuff.c_str();
  while (nleft > 0) {
    if ((nwritten = write(fd, ptr, nleft)) <= 0) {
      if (nwritten < 0) {
        if (errno == EINTR) {
          nwritten = 0;
          continue;
        } else if (errno == EAGAIN)
          break;
        else
          return -1;
      }
    }
    writeSum += nwritten;
    nleft -= nwritten;
    ptr += nwritten;
  }
  if (writeSum == static_cast<int>(sbuff.size()))
    sbuff.clear();
  else
    sbuff = sbuff.substr(writeSum);
  return writeSum;
}

void handle_for_sigpipe() {
  struct sigaction sa;
  memset(&sa, '\0', sizeof(sa));
  sa.sa_handler = SIG_IGN;
  sa.sa_flags = 0;
  if (sigaction(SIGPIPE, &sa, NULL))
     return;
}

int setSocketNonBlocking(int fd) {
  int flag = fcntl(fd, F_GETFL, 0);
  if (flag == -1) return -1;

  flag |= O_NONBLOCK;
  if (fcntl(fd, F_SETFL, flag) == -1) return -1;
  return 0;
}
//发送数据时候系统缓冲区有数据就立刻发送
void setSocketNodelay(int fd) {
  int enable = 1;
  setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void *)&enable, sizeof(enable));
    //int setsockopt( int socket, int level, int option_name,const void *option_value, size_t ，ption_len);
  //第一个参数socket是套接字描述符。第二个参数level是被设置的选项的级别，
    //如果想要在套接字级别上设置选项，就必须把level设置为 SOL_SOCKET。 
    //option_name指定准备设置的选项，option_name可以有哪些取值，这取决于level
}

void setSocketNoLinger(int fd) {
  struct linger linger_;
  linger_.l_onoff = 1;
  linger_.l_linger = 30;
  setsockopt(fd, SOL_SOCKET, SO_LINGER, (const char *)&linger_,
             sizeof(linger_));
}

void shutDownWR(int fd) {
  shutdown(fd, SHUT_WR);
}

int socket_bind_listen(int port) {
  // 检查port值，取正确区间范围
  if (port < 0 || port > 65535) return -1;

  // 创建socket(IPv4 + TCP)，返回监听描述符
  int listen_fd = 0;
  //第一个参数IPV4，第二个参数SOCK_STREAM 是数据流,一般是tcp/ip协议的编程，第三个参数使用0则根据前两个参数使用默认的协议。　
  if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) return -1;

  // 消除bind时"Address already in use"错误
  //closesocket（一般不会立即关闭而经历TIME_WAIT的过程）后想继续重用该socket
  //一般来说，一个端口释放后会等待两分钟之后才能再被使用，SO_REUSEADDR是让端口释放后立即就可以被再次使用。     
//SO_REUSEADDR用于对TCP套接字处于TIME_WAIT状态下的socket，允许重复绑定使用。
//server程序总是应该在调用bind()之前设置SO_REUSEADDR套接字选项
  int optval = 1;
  if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval,
                 sizeof(optval)) == -1) {
    close(listen_fd);
    return -1;
  }
  // 设置服务器IP和Port，和监听描述副绑定
  struct sockaddr_in server_addr;
  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;                  //ipv4协议
  //INADDR_ANY 的具体含义是，绑定到0.0.0.0。此时，对所有的地址都将是有效的，如果系统考虑冗余，采用多个网卡的话，
  //那么使用此种bind，将在所有网卡上进行绑定。在这种情况下，你可以收到发送到所有有效地址上数据包。
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   //任意端口,htonl是将主机数转换成无符号长整形的网络字节顺序
  server_addr.sin_port = htons((unsigned short)port); //将主机的无符号短整形数转换成网络字节顺序。
  if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==  // 绑定网卡和端口
      -1) {
    close(listen_fd);
    return -1;
  }
  // 开始监听，最大等待队列长为LISTENQ
  if (listen(listen_fd, 2048) == -1) {
    close(listen_fd);
    return -1;
  }
  // 无效监听描述符
  if (listen_fd == -1) {
    close(listen_fd);
    return -1;
  }
  return listen_fd;
}
//于应用服务器来说，如果ACCEPT队列中有已经建立好的TCP连接，却没有及时把它取出来，这样，一旦导致两个队列满之后，
//就会使客户端不能再建立新连接，引发严重问题。所以，一些服务器会使用一个主进程来做accept获取连接，
//而让其他工作进程来进行其他数据处理等工作，这样可以防止不能及时的去accept获取连接。