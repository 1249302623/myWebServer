#pragma once
#include"noncopyable.h"
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
template<typename T>
class Singleton:noncopyable{
public:
    static T& instance(){
        pthread_once(&ponce_,&Singleton::init);
        return *value_;
    }
private:
    Singleton();
    ~Singleton();
    static pthread_once_t ponce_;//pthread_once 需要是静态的
    static T* value_;
    static void init(){
        value_=new T();
        atexit(destory);////其作用是注册某一个函数，当进程执行结束时，会自动调用注册的函数
    }
    static void destory(){
        typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
    //定义了一个固定大小的char型数组，数组名为type_must_be_complete，数组大小是多少呢？是sizeof(T)?1:-1
        delete value_;
        //printf("destory\n");
    }
};
template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = NULL;