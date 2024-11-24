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
        static std::ofstream file{"output.txt"};
        std::lock_guard<std::mutex> lock(mutex);
        file << message << std::endl;
    }
};

class Thread
{
public:
    void start(std::function<void(void)> workerThreadCallback)
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (isThreadRunning)
        {
            return;
        }
        isThreadRunning = true;
        thread = std::thread([this, workerThreadCallback]() -> void
                             {
            while(isThreadRunning)
            {
                workerThreadCallback();
                sleep(1);
            } });
    }
    void stop()
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (!isThreadRunning)
        {
            return;
        }
        if (thread.joinable())
        {
            isThreadRunning = false;
            thread.join();
        }
    }
    ~Thread()
    {
        stop();
    }

private:
    std::thread thread;
    bool isThreadRunning = false;
    std::mutex mutex;
};
