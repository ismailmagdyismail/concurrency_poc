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
    Router router{2};
    Device d1{&router, 1};
    Device d2{&router, 2};
    Device d3{&router, 3};
    std::cout << "Devices started \n";
    while (true)
    {
        int deviceToStopId;
        std::cout << "Enter device Id to stop: ";
        std::cin >> deviceToStopId;
        router.disconnect(deviceToStopId);
    }
}
