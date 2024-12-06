#include "MessageBus.hpp"

void MessageBus::addMessage(int id, const std::string &message)
{
  std::lock_guard<std::mutex> lock(m_messagesMutex);
  m_messages[id] = message;
}

std::string MessageBus::readMessage(int id)
{
  std::lock_guard<std::mutex> lock(m_messagesMutex);
  if (m_messages.find(id) == m_messages.end())
  {
    return "";
  }
  return m_messages[id];
}