#include <mutex>
#include <stack>
#include <iostream>
#include <thread>
#include <vector>

class ThreadSafeStack
{
public:
    int top()
    {
        std::lock_guard<std::recursive_mutex>lock(this->stackMutex);
        return s.top();
    }
    void pop()
    {
        std::lock_guard<std::recursive_mutex>lock(this->stackMutex);
        s.pop();
    }
    bool isEmpty()
    {
        std::lock_guard<std::recursive_mutex>lock(this->stackMutex);
        return s.empty();
    }
    void executeAtomicOperation(void (*callback)(ThreadSafeStack& stack))
    {
        std::lock_guard<std::recursive_mutex>lock(this->stackMutex);
        if(callback)
        {
            callback(*this);
        }
    }
    void push(int val)
    {
        std::lock_guard<std::recursive_mutex>lock(this->stackMutex);
        s.push(val);
    }
private:
    std::stack<int> s;
    std::recursive_mutex stackMutex ;
};
int main()
{
    int threadsCount = 10;
    std::vector<std::thread> threads(threadsCount);
    ThreadSafeStack s;
    for(int i = 0 ; i< 100 ;i++){
        s.push(10);
    }
    for(int i = 0 ; i < threadsCount ; i++)
    {
        void (*callBack)(ThreadSafeStack& stack) = [](ThreadSafeStack& stack)->void{
            while(!stack.isEmpty())
            {
                std::cout<<"Thread exec "<<std::this_thread::get_id()<<'\n';
                stack.pop();
            }
        };
        threads[i] = std::thread([&]()->void{
            std::cout<<"thread starting\n";
            s.executeAtomicOperation(callBack);
        });
    }
    for(int i = 0 ; i<threadsCount;i++)
    {
        if(threads[i].joinable())
        {
            std::cout<<"Joining "<<std::this_thread::get_id()<<'\n';
            threads[i].join();
        }
    }
}
