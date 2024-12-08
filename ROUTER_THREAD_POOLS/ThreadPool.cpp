#include <mutex>

#include "ThreadPool.hpp"
#include "Logger.hpp"

ThreadPool::ThreadPool(int poolSize)
{
    m_stopped = false;
    for (int i = 0; i < poolSize; i++)
    {
        threadPool.emplace_back(std::thread(&ThreadPool::workerThread, this));
    }
}

void ThreadPool::addTask(std::function<void(void)> workerThread)
{
    std::unique_lock<std::mutex> lock(tasksMutex);
    tasks.push(workerThread);
    m_cv.notify_one();
}

void ThreadPool::workerThread()
{
    while (true)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(tasksMutex);
            m_cv.wait(lock, [this]
                      { return m_stopped || !tasks.empty(); });
            if (m_stopped && tasks.empty())
            {
                return;
            }
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}

ThreadPool::~ThreadPool()
{
    m_stopped = true;
    m_cv.notify_all();
    for (int i = 0; i < threadPool.size(); i++)
    {
        if (threadPool[i].joinable())
        {
            threadPool[i].join();
        }
    }
}
