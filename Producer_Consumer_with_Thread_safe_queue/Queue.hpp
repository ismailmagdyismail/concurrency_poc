#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

class Queue
{
public:
    void pop(int& outElement);
    std::shared_ptr<int>pop();
    bool tryPop(int& outElement);
    std::shared_ptr<int>tryPop();
    void push(int element);
    bool isEmpty();

private:
    bool lockFreeIsEmpty();
    std::mutex queueMutex;
    std::condition_variable queueCv;
    std::queue<int> queue;
};
