#pragma once

#include <iostream>
#include <map>

class MessageBus
{
public:
  void addMessage(int messageId, const std::string &message);
  std::string readMessage(int messageId);

private:
  std::mutex m_messagesMutex;
  std::unordered_map<int, std::string> m_messages; // messageId , message
};