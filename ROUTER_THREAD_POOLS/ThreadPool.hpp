#pragma once

#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>

class ThreadPool
{
public:
    ThreadPool(int poolSize);
    void addTask(std::function<void(void)> workerThread);
    void stop();
    ~ThreadPool();

private:
    void workerThread();

    //! threadPool running state
    std::atomic<bool> m_stopped;

    //! tasksQueue
    std::queue<std::function<void(void)>> tasks;
    std::mutex tasksMutex;

    //! active threads
    std::vector<std::thread> threadPool;
    std::condition_variable m_cv;
};
