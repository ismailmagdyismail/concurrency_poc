#include <climits>
#include <mutex>
#include <iostream>
#include <stdexcept>
#include <thread>

class HierarchialMutex
{
public:
    explicit HierarchialMutex(unsigned long hierarhcyValue):heirarchyValue(hierarhcyValue),previousValue(0){}

    void lock()
    {
        checkHierarchy();
        mx.lock();
        updateHierarchy();
    }

    void unlock()
    {
        if(thisThreadValue != heirarchyValue)
        {
            throw std::logic_error("Out of order unlocking");
        }
        thisThreadValue = previousValue;
        mx.unlock();
    }
private:

    void checkHierarchy()
    {
        if(thisThreadValue <= heirarchyValue)
        {
            throw std::logic_error("Out of order hierarchy");
        }
    }

    void updateHierarchy()
    {
        previousValue = thisThreadValue;
        thisThreadValue = heirarchyValue;
    }
    // last value used to lock the thread
    unsigned long heirarchyValue;

    // previous value that that thread was locked from , NOTE: not static but per Mutex instead
    // so that on each unlock done by each mutex thread can roll back to previous valaue in a stack-like fashion
    // if it were static it would have to be stored as stack to store all previous values
    // now each mutex itself knows its previous value and set it to the thread on UNLOCKING
    unsigned long previousValue;

    // a static variabel ,BUT LOCAL to EACH THREAD
    // stores the current hierarchy level of that thread so that we can track and prevent locks out of order
    static thread_local unsigned long thisThreadValue;

    std::mutex mx;

};

thread_local unsigned long HierarchialMutex::thisThreadValue = ULONG_MAX;


HierarchialMutex high(10);
HierarchialMutex mid(5);
HierarchialMutex low(1);


void lowLevelStuf()
{
    std::lock_guard<HierarchialMutex> lock(low);
}
void highLevelStuff()
{
    std::lock_guard<HierarchialMutex> lock(high);
    lowLevelStuf();
}
void other()
{
    std::lock_guard<HierarchialMutex> lock(mid);
    highLevelStuff();
}

int main()
{
    other(); // should throw
    // highLevelStuff(); shouldn't throw
}
