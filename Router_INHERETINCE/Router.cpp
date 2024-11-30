#include "Router.hpp"
#include "Device.hpp"
#include "Thread.hpp"
#include <string>

Router::Router(int connectionLimit) : connectionLimit(connectionLimit)
{
    //! NOTE : if start was virtual this would cause undefined behaviour since vtable is not yet constructed
    start(std::bind(&Router::broadcastData, this));
}

void Router::connect(Device *device)
{
    mutex.lock();
    while (connections.size() >= connectionLimit)
    {
        mutex.unlock();
        sleep(2);
        mutex.lock();
    }
    connections[device->id] = device;
    mutex.unlock();
}

void Router::disconnect(int id)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (connections.find(id) == connections.end())
    {
        Logger::log("connection Not found " + std::to_string(id));
        return;
    }
    // WHY stop the device here ? breaks encapsulation => stop it in the device itself,  or use callbacks
    connections[id]->stop();
    connections.erase(id);
    Logger::log("connection removed " + std::to_string(id));
}

void Router::broadcastData()
{
    std::lock_guard<std::mutex> lock(mutex);
    for (auto &connection : connections)
    {
        connection.second->acceptMessage(std::string("Router message ") + std::to_string(messageId));
    }
    messageId++;
}

Router::~Router()
{
    for (auto &connection : connections)
    {
        connection.second->stop();
    }
    stop();
}
