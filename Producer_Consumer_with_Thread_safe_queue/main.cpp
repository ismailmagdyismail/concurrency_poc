#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
#include <atomic>

#include "Logger.hpp"
#include "Queue.hpp"

Queue dataQueue;

void producer()
{
    // would required
    static std::atomic<int> counter = 0   ;
    while (true)
    {
        dataQueue.push(counter);
        Logger::log("Producer: " + std::to_string(counter));
        counter++;
        sleep(1);
    }

}

void consumer()
{
    while (true)
    {
        Logger::log("Consumed:" + std::to_string(*dataQueue.pop()));
        sleep(1);
    }
}

void try_consumer()
{
    while (true)
    {
        int element;
        bool isPopped = dataQueue.tryPop(element);
        if(isPopped)
        {
            Logger::log("Consumed: " + std::to_string(element));
        }
        else
        {
            Logger::log("Consumed: Empty Queue");

        }
        sleep(1);
    }
}

int main()
{
    std::thread t1{producer};
    std::thread t2{try_consumer};

    while (true)
    {    }
}
