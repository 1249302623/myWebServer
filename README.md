# liuServer仿muduo库，多reactor模式模拟Proactor模式的C++高性能高并发HTTP服务器

## 介绍 

本项目为linux下C++11编写的Web资源服务器，支持web端用户实现注册、登录功能，可以请求服务器图片和视频文件，实现同步/异步日志系统，记录服务器运行状态，经压力测试可以实现至少两万的并发连接客户端，50s内处理请求200w个，0失败，每秒响应请求4w多个。


## 环境 
* 操作系统: Ubuntu 16.04.12
* 编译器: g++ 5.4.0
* IDE：vscode
* 服务器配置：4核8G华为云主机
* 数据库：mysql
## 运行
进入build目录，执行./LiuServerPro文件

*cd build

*./LiuServerPro

## 运用技术
* 使用主从Reactor线程池模拟Proactor模式，reactor线程池充当Proactor的异步IO线程。
* 使用Epoll边沿触发的IO多路复用技术构建Reactor线程池，主reactor线程只负责accept请求，并以RoundRobin的方式分发给从reactor线程。从reactor线程池在接收完数据后通知Proactor用户线程。
* 构建Proactor用户线程池，对tcp数据进行处理，执行用户函数。
* 使用基于小根堆的定时器关闭超时请求
* 使用muduo库的buffer类实现高性能的输入输出缓冲区
* 使用eventfd实现了线程的异步唤醒
* 使用双缓冲区技术实现了异步日志系统
* 使用状态机解析HTTP请求报文，支持解析GET和POST请求
* 访问服务器数据库实现web端用户注册、登录功能，可以请求服务器图片和视频文件
* 为减少内存泄漏的可能，使用智能指针等RAII机制
* 重构了muduo库的框架，用继承和虚函数的方式代替了回调函数，框架更加清晰。
 
## 模型

并发模型为主从Reactor线程池(Procator异步线程）+用户线程池（Proactor同步线程）。
![image](/TestPic/模型图.png)
## 参考
* 本文主要参考自陈硕老师muduo库
https://github.com/chenshuo/muduo
* Reactor线程池，有限状态机和定时器部分参考
https://github.com/linyacool/WebServer
* 数据库连接池部分和HTML文件摘自
https://github.com/qinguoyi/TinyWebServer

## 测试
使用Apache Benchmark(简称ab)进行服务器压力测试，ab是Apache安装包中自带的压力测试工具.
输入命令：
 ab -t 60 -n 2000000 -c 20000 -r -k http://127.0.0.1:8080/
 
 命令解释：测试实现限制在60s,并发连接用户数2w个（2w并不是服务器的最大连接数，而是ab压力测试所能模拟的最大客户端数量），并发请求数200w个  ,保持常连接，出错时直接返回，结果如下：
 ![image](/TestPic/2w客户端200w请求.png)

可以看到，
完成请求200w次，0失败
每秒响应请求数41036次，
带宽21239.4kb/s,
最大请求响应时间797ms

## 演示
web端用户实现注册、登录功能，可以请求服务器图片和视频文件
![Watch the video](/TestPic/服务器演示.mp4)
