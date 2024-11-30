#pragma once

#include "Router.hpp"
#include "Thread.hpp"


class Router;

class Device
{
public:
    Device(Router* router,int id );
    void unRegisterRouter();
    void registerRouter(Router* router);
    void acceptMessage(const std::string& message);
    ~Device();
    int id;
private:
    std::mutex mutex;
    void doSomeWork();
    Router* router;
    Thread thread;
    bool connected = false;
};
