#pragma once

#include "Thread.hpp"
#include <condition_variable>
#include <unordered_map>
#include <mutex>

class Device;

class Router
{
public:
    Router(int connectionsCount);
    void connect(Device* device);
    void disconnect(int deviceId);
    ~Router();
private:
    int connectionsLimit;
    std::mutex mutex;
    std::condition_variable cv;
    void broadcastData();
    int messageCount = 1;
    std::unordered_map<int , Device*> connections;
    Thread thread;
};
