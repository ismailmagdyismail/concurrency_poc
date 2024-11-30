#include "Device.hpp"
#include "Router.hpp"
#include "Thread.hpp"
#include <mutex>
#include <string>
#include <future>
#include <thread>

Device::Device(Router *router, int id)
{
    this->router = router;
    this->id = id;
    start();
}

void Device::acceptMessage(std::string message)
{
    Logger::log(message + " to Device " + std::to_string(id));
}

void Device::start()
{
    Thread::start(std::bind(&Device::someWork, this));
    // std::lock_guard<std::mutex> lock(mutex);
    // if (!connected)
    // {
    //     std::thread t([this]()
    //                   {
    //         router->connect(this);
    //         mutex.lock();
    //         connected = true;
    //         mutex.unlock();
    //         Thread::start(std::bind(&Device::someWork, this)); });
    //     t.detach();
    // }
}
void Device::someWork()
{
    mutex.lock();
    if (!connected)
    {
        router->connect(this);
        connected = true;
    }
    mutex.unlock();
    Logger::log("Device " + std::to_string(id) + " : doing work");
}

void Device::stop()
{
    std::lock_guard<std::mutex> lock(mutex);
    connected = false;
    Thread::stop();
}
