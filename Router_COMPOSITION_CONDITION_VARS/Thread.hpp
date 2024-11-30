#pragma once

#include <functional>
#include <string>
#include <thread>
#include <map>
#include <mutex>
#include <unistd.h>
#include <iostream>
#include <fstream>

namespace Logger
{
    static void log(std::string message)
    {
        static std::mutex mutex;
        static std::ofstream file{"output2.txt"};
        std::lock_guard<std::mutex> lock(mutex);
        file << message << std::endl;
    }
};

class Thread
{
public:
    Thread()
    {
        isThreadRunning = false;
    }
    void start(std::function<void(void)> callback)
    {
        std::lock_guard<std::mutex>lock(mutex);
        if(isThreadRunning)
        {
            return;
        }
        isThreadRunning = true;
        thread = std::thread([this,callback]()->void {
            while(isThreadRunning)
            {
                callback();
                sleep(1);
            }
        });
    }
    void stop()
    {
        if(!isThreadRunning)
        {
            return;
        }
        std::lock_guard<std::mutex>lock(mutex);
        isThreadRunning = false;
        if(thread.joinable())
        {
            thread.join();
        }
    }
    ~Thread()
    {
        stop();
    }
private:
    std::thread thread;
    bool isThreadRunning;
    std::mutex mutex;
};
