//! system includes
#include <memory>
#include <mutex>

#include "Router.hpp"
#include "Device.hpp"
#include "ThreadPool.hpp"
#include "MessageBus.hpp"
#include <unistd.h>

Router::Router(int maxConnectionsCount, std::shared_ptr<ThreadPool> pool, std::shared_ptr<MessageBus> messageBus)
{
    m_maxConnectionsCount = maxConnectionsCount;
    m_pool = pool;
    m_messageBus = messageBus,
    m_pool->addTask(std::bind(&Router::broadcastMessage, this));
}

void Router::connect(Device *device)
{
    std::unique_lock<std::mutex> lock(m_connectionsMutex);
    m_connectionsConditionVariable.wait(lock, [this]()
                                        { return m_connectedDevices.size() < m_maxConnectionsCount; });
    m_connectedDevices[device->m_id] = device;
    m_connectionsConditionVariable.notify_all();
}

void Router::disconnect(int deviceId)
{
    std::lock_guard<std::mutex> lock(m_connectionsMutex);
    m_connectedDevices[deviceId]->disconnect();
    m_connectedDevices.erase(deviceId);
    m_connectionsConditionVariable.notify_all();
}

void Router::broadcastMessage()
{
    while (true)
    {
        std::lock_guard<std::mutex> lock(m_messageIdMutex);
        m_messageBus->addMessage(m_messageId, std::string("Router Broadcast message ") + std::to_string(m_messageId));
        m_messageId++;
        sleep(2);
    }
}

Router::~Router()
{
}