#pragma once
#include <memory>
#include <vector>
#include "ConnThread.h"
#include "Logging.h"
#include "noncopyable.h"


class ConnThreadPool : noncopyable {
 public:
  ConnThreadPool(EventLoop* baseLoop, int numThreads);

  ~ConnThreadPool() { LOG_INFO<< "~ConnThreadPool()"; }
  void start();

  EventLoop* getNextLoop();

private:
  EventLoop* baseLoop_;
  bool started_;
  int numThreads_;
  int next_;
  std::vector<std::shared_ptr<ConnThread>> connThreads_;
  std::vector<EventLoop*> loops_;
};
