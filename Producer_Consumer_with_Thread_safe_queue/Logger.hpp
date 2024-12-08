#pragma once

#include <iostream>
#include <fstream>

namespace Logger
{
  static void log(std::string message)
  {
    static std::mutex mutex;
    static std::ofstream file{"output.txt"};
    std::lock_guard<std::mutex> lock(mutex);
    file << message << std::endl;
  }
};
