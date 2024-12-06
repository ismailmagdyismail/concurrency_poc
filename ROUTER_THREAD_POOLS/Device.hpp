#pragma once

#include "MessageBus.hpp"
#include "ThreadPool.hpp"

class Router;

class Device
{
public:
    Device(int id, std::shared_ptr<Router>, std::shared_ptr<ThreadPool>, std::shared_ptr<MessageBus>);
    void disconnect();
    int m_id;

private:
    void acceptMessages();

    std::mutex m_runningMutex;
    bool m_stopped;

    //! messages
    int m_messageToRead;
    std::mutex m_messagesIdMutex;

    //! router
    bool m_connected;
    std::mutex m_connectedMutex;
    std::shared_ptr<Router> m_router;

    //! threadPool
    std::shared_ptr<ThreadPool> m_pool;

    //! router
    std::shared_ptr<MessageBus> m_messageBus;
};
