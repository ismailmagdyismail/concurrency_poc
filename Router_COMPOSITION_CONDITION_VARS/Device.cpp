#include "Device.hpp"
#include "Router.hpp"
#include <mutex>

Device::Device(Router *router, int id)
{
    this->router = router;
    this->id = id;
    thread.start(std::bind(&Device::doSomeWork, this));
}

void Device::acceptMessage(const std::string &message)
{
    Logger::log(message + " to Device " + std::to_string(id));
}

void Device::doSomeWork()
{
    mutex.lock();
    if (!router)
    {
        Logger::log("Device " + std::to_string(id) + " : Not connected");
        mutex.unlock();
        return;
    }
    if (!connected)
    {
        Logger::log("Device " + std::to_string(id) + " : Attempting to connect");
        router->connect(this);
        connected = true;
    }
    mutex.unlock();
    Logger::log("Device " + std::to_string(id) + " : doing work");
}

void Device::registerRouter(Router *router)
{
    std::lock_guard<std::mutex> lock(mutex);
    this->router = router;
}

void Device::unRegisterRouter()
{
    std::lock_guard<std::mutex> lock(mutex);
    connected = false;
    this->router = nullptr;
}

Device::~Device()
{
    router->disconnect(id);
    this->router = nullptr;
    thread.stop();
}
