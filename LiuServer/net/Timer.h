//借鉴了Lin Ya大佬的实现
#pragma once
#include <unistd.h>
#include <deque>
#include <memory>
#include <queue>
#include "ConnChannel.h"
#include "MutexLock.h"
#include "noncopyable.h"
#include"Timestamp.h"
typedef std::shared_ptr<TimerNode> SPTimerNode;
class TimerNode:noncopyable {
 public:
  TimerNode(ConnChannel* requestData, int timeout);
  ~TimerNode();
  TimerNode(const TimerNode &tn);
  void update(int timeout);
  bool isValid();
  void clearReq();
  void setDeleted() { deleted_ = true; }
  bool isDeleted() const { return deleted_; }
  Timestamp getExpTime() const { return expiredTime_; }

private:
  bool deleted_;
  Timestamp expiredTime_;
  ConnChannel* connChannelPtr_;
};

struct TimerCmp {
  bool operator()(SPTimerNode a,SPTimerNode b) const {
    return a->getExpTime().microSecondsSinceEpoch()> b->getExpTime().microSecondsSinceEpoch();
  }
};

class TimerManager {
public:
  TimerManager();
  ~TimerManager();
  void addTimer(ConnChannel*, int timeout);
  void handleExpiredEvent();

 private:
  typedef std::shared_ptr<TimerNode> SPTimerNode;
  std::priority_queue<SPTimerNode, std::vector<SPTimerNode>, TimerCmp>
      timerNodeQueue;
};