#pragma once

#include<stdio.h>
#include<stdint.h>
#include<string>
#include"noncopyable.h"
class Timestamp
{
private:
    int64_t microSecondsSinceEpoch_;//微秒形式
public:
    static const int kMicroSecondsPerSecond = 1000 * 1000;
    Timestamp():microSecondsSinceEpoch_(0){};
    Timestamp(int64_t microSecondsSinceEpochArg)
        :microSecondsSinceEpoch_(microSecondsSinceEpochArg)
    {       
    }
    std::string toString() const;
    std::string toFormattedString(bool showMicroseconds=true)const;

    bool valid() const {return microSecondsSinceEpoch_>0;}
    int64_t microSecondsSinceEpoch() const{
        return this->microSecondsSinceEpoch_;
    }
    time_t secondsSinceEpoch() const{
        return static_cast<time_t>(this->microSecondsSinceEpoch_/kMicroSecondsPerSecond);
    }
    static Timestamp now();
    static Timestamp invalid(){//得到一个空对象
        return Timestamp();
    }

    static Timestamp fromYnixTime(time_t t,int microseconds){
        return Timestamp(static_cast<int64_t>(t
            *kMicroSecondsPerSecond)+microseconds);
    }
    //~Timestamp();
};
inline bool operator<(Timestamp lhs,Timestamp rhs){
    return lhs.microSecondsSinceEpoch()<rhs.microSecondsSinceEpoch();
}
inline bool operator>(Timestamp lhs,Timestamp rhs){
    return lhs.microSecondsSinceEpoch()>rhs.microSecondsSinceEpoch();
}
inline bool operator==(Timestamp lhs,Timestamp rhs){
    return lhs.microSecondsSinceEpoch()==rhs.microSecondsSinceEpoch();
}
inline double timeDifference(Timestamp high,Timestamp low){
    int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
    return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}
inline Timestamp addTime(Timestamp timestamp, double seconds)
{
  int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
  return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}
