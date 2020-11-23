#pragma once
#include<pthread.h>
#include"noncopyable.h"
template<typename T>
class ThreadLocal:noncopyable{
public:
    ThreadLocal(){
        pthread_key_create(&pkey_,&ThreadLocal::destructor);//第二个参数在线程释放该线程存储的时候被调用
    }
    ~ThreadLocal(){
        pthread_key_delete(pkey_);
    }
    T& value(){
        T* perThreadValue=static_cast<T*>(pthread_getspecific(pkey_));
        if(!perThreadValue){//如果非空
            T* newObj=new T();//在获得值的时候才执行构造函数
            pthread_setspecific(pkey_,newObj);
            perThreadValue=newObj;
        }
        return *perThreadValue;
    }
private:
    pthread_key_t pkey_;
    static void destructor(void* x){//销毁程序
        T* obj=static_cast<T*>(x);
        typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
        delete obj;
    }
};
// 在单线程程序中，我们经常要用到"全局变量"以实现多个函数间共享数据。但是在多线程环境下，由于数据空间是共享的，因此全局变量也为所有线程所共有。 然而时应用程序设计中有必要提供线程私有的全局变量，仅在某个线程中有效，但却可以跨多个函数访问。
// POSIX线程库通过维护一定的数据结构来解决这个问题，这个些数据称为（Thread-specific Data，或 TSD）。
// 线程特定数据也称为线程本地存储TLS（Thread-local storage），对于POD类型的线程本地存储，可以用__thread关键字。
// 下面说一下线程存储的具体用法。
// - 创建一个类型为pthread_key_t类型的变量。
// - 调用pthread_key_create()来创建该变量。该函数有两个参数，第一个参数就是上面声明的pthread_key_t变量，第二个参数是一个清理函数，用来在线程释放该线程存储的时候被调用。该函数指针可以设成 NULL，这样系统将调用默认的清理函数。该函数成功返回0.其他任何返回值都表示出现了错误。
// - 当线程中需要存储特殊值的时候，可以调用 pthread_setspcific() 。该函数有两个参数，第一个为前面声明的pthread_key_t变量，第二个为void*变量，这样你可以存储任何类型的值。
// - 如果需要取出所存储的值，调用pthread_getspecific()。该函数的参数为前面提到的pthread_key_t变量，该函数返回void *类型的值。
// 下面是前面提到的函数的原型：
// 	int pthread_setspecific(pthread_key_t key, const void *value);
// 	void *pthread_getspecific(pthread_key_t key);
// 	int pthread_key_create(pthread_key_t *key, void (*destructor)(void*));