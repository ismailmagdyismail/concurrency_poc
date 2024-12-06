#pragma once

//! system includes
#include <memory>
#include <mutex>
#include <unordered_map>

#include "ThreadPool.hpp"
#include "MessageBus.hpp"

class Device;

class Router
{
public:
    Router(int maxConnectionsCount, std::shared_ptr<ThreadPool> pool, std::shared_ptr<MessageBus> messageBus);
    void connect(Device *device);
    void disconnect(int deviceId);
    ~Router();

private:
    void broadcastMessage();

    //! connections
    int m_maxConnectionsCount;
    std::unordered_map<int, Device *> m_connectedDevices;
    std::mutex m_connectionsMutex;
    std::condition_variable m_connectionsConditionVariable;

    //! messages
    std::mutex m_messageIdMutex;
    int m_messageId;

    //! threadPool
    std::shared_ptr<ThreadPool> m_pool;

    //! messageBus
    std::shared_ptr<MessageBus> m_messageBus;
};
