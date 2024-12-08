#include "Queue.hpp"
#include <memory>
#include <mutex>

void Queue::push(int element)
{

    {
        std::lock_guard<std::mutex>lock(queueMutex);
        queue.push(element);
        //! lock released before notifying ,
        //!  to make sure that other waiting threads don't sleep one extra time as a result of the lock still being held
    }
    queueCv.notify_one();
}

void Queue::pop(int& outElement)
{
    std::unique_lock<std::mutex>lock(queueMutex);

    //! NOTE: this will cause double locking since the CV already locks before checking condition , ans isEmpty() locks same lock
    // queueCv.wait(lock,[this]()->bool{return !isEmpty();});

    queueCv.wait(lock,[this]()->bool{return !lockFreeIsEmpty();});
    outElement = queue.front();
    queue.pop();
}

std::shared_ptr<int> Queue::pop()
{
    int element;
    //! reuse already blocking implementation of pop
    pop(element);
    return std::make_shared<int>(std::move(element)); // MOVE here is not useful for ints , but could be for big objets
}

bool Queue::tryPop(int& outElement)
{
    // NOTE : this code is not safe , the after the isEmpty check the thread could be swapped out,  another thread could pop element  and queue will then be Empty
    // if(isEmpty())
    // {
    //     return false;
    // }
    // std::lock_guard<std::mutex>lock(queueMutex);
    // outElement = queue.front();
    // queue.pop();
    // return true;


    //! keep lock for whole duration of popping
    std::lock_guard<std::mutex>lock(queueMutex);
    if(lockFreeIsEmpty())
    {
        return false;
    }
    outElement = queue.front();
    queue.pop();
    return true;
}

std::shared_ptr<int> Queue::tryPop()
{
    int element;
    bool isPoppedSuccessfully = tryPop(element);
    if(isPoppedSuccessfully)
    {
        return std::make_shared<int>(std::move(element));
    }
    return nullptr;
}

bool Queue::isEmpty()
{
    std::lock_guard<std::mutex>lock(queueMutex);
    return lockFreeIsEmpty();
}

bool Queue::lockFreeIsEmpty()
{
    // assume complex logic here
    return queue.empty();
}
