#include <functional>
#include <mutex>
#include <string>

#include "Router.hpp"
#include "Device.hpp"
#include "Thread.hpp"

Router::Router(int connectionsLimit)
{
    this->connectionsLimit = connectionsLimit;
    thread.start(std::bind(&Router::broadcastData,this));
}

void Router::connect(Device *device)
{
    {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this]() { return connections.size() < connectionsLimit; });
        connections[device->id] = device;
        Logger::log("connected "+std::to_string(device->id));
    }
    cv.notify_all();
}

void Router::disconnect(int id)
{
    {
        std::unique_lock<std::mutex>lock(mutex);
        if(connections.find(id) == connections.end())
        {
             Logger::log("connection doens't exist " + std::to_string(id));
             return;
        }
        connections[id]->unRegisterRouter();
        connections.erase(id);
        Logger::log("connection removed " + std::to_string(id));
    }
    cv.notify_all();
}

void Router::broadcastData()
{
    std::lock_guard<std::mutex>lock(mutex);
    for(auto& connection : connections)
    {
        connection.second->acceptMessage(std::string("Router message ") + std::to_string(messageCount));
    }
    messageCount++;
}

Router::~Router()
{
    for(auto& connection : connections)
    {
        connection.second->unRegisterRouter();
    }
    connections.clear();
    thread.stop();
}
