#pragma once
#include "Thread.hpp"

class Device ;

class Router : private Thread
{
public:
    Router(int connectionLimit);
    void connect(Device* device);
    void disconnect(int id);
    ~Router();
private:
    void broadcastData();
    std::map<int,Device*> connections;
    int connectionLimit;
    std::mutex mutex;
    int messageId = 1 ;
};
