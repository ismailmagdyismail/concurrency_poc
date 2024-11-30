#pragma once
#include "Thread.hpp"
#include <mutex>

class Router;

class Device: public Thread
{
public:
    Device(Router* router,int id);
    void acceptMessage(std::string message);
    void stop();
    void start();
    int id;
private:
    std::mutex mutex;
    void someWork();
    Router* router;
    bool connected = false;
};
