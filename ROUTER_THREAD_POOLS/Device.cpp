#include <unistd.h>

#include "Device.hpp"
#include "Logger.hpp"
#include "Router.hpp"

Device::Device(int id, std::shared_ptr<Router> router, std::shared_ptr<ThreadPool> pool, std::shared_ptr<MessageBus> bus)
{
  m_id = id;
  m_router = router;
  m_pool = pool;
  m_messageBus = bus;
  m_messageToRead = 0;
  m_stopped = false;

  m_pool->addTask(std::bind(&Device::acceptMessages, this));
}

void Device::acceptMessages()
{
  m_runningMutex.lock();
  while (!m_stopped)
  {
    m_connectedMutex.lock();
    if (!m_connected)
    {
      Logger::log("attempting to connect " + std::to_string(m_id));
      m_router->connect(this);
      Logger::log("Connected" + std::to_string(m_id));
      m_connected = true;
    }
    m_connectedMutex.unlock();
    std::string readMessage = m_messageBus->readMessage(m_id);
    if (readMessage.empty())
    {
      continue;
    }
    m_runningMutex.unlock();
    Logger::log("Device " + std::to_string(m_id) + "reading message " + std::to_string(m_messageToRead) + " " + readMessage);
    m_messagesIdMutex.lock();
    m_messageToRead++;
    m_messagesIdMutex.unlock();

    sleep(2);
    m_runningMutex.lock();
  }
}

void Device::disconnect()
{
  std::lock_guard<std::mutex> lock(m_runningMutex);
  m_stopped = false;
}