#include "Device.hpp"
#include "Router.hpp"
#include <functional>
#include <string>
#include <thread>
#include <map>
#include <mutex>
#include <unistd.h>
#include <iostream>

int main()
{
  std::cout << "Main thread\n";

  int threadPoolSize = 5;
  std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>(threadPoolSize);

  std::shared_ptr<MessageBus> messageBus = std::make_shared<MessageBus>();

  std::shared_ptr<Router> router = std::make_shared<Router>(2, pool, messageBus);

  Device d1{1, router, pool, messageBus};
  Device d2{2, router, pool, messageBus};
  Device d3{3, router, pool, messageBus};

  std::cout << "Devices started \n";
  while (true)
  {
    int deviceToStopId;
    std::cout << "Enter device Id to stop: ";
    std::cin >> deviceToStopId;
    router->disconnect(deviceToStopId);
  }
}