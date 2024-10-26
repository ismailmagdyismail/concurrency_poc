#include <memory>
#include <mutex>
#include <stack>
#include <iostream>
#include <utility>

class ThreadStackStack
{
public:
    std::shared_ptr<int> pop()
    {
        std::lock_guard<std::mutex> lock(stackMutex);
        if(s.empty()){
            return std::make_shared<int>(nullptr);
        }
        std::shared_ptr<int> top = std::make_shared<int>(s.top()); // NOTE: even if this throws std::bad_alloc the top value is still within stack , not lost
        s.pop();
        return top;
    }
    void pop(int& out)
    {
        std::lock_guard<std::mutex>lock(stackMutex);
        if(s.empty())
        {
            return;
        }
        out = s.top(); // NOTE: even if this throws std::bad_alloc the top value is still within stack , not lost
        s.pop();
    }
    bool empty()
    {
        std::lock_guard<std::mutex>lock(stackMutex);
        return s.empty();
    }
    void push(int x )
    {
        std::lock_guard<std::mutex>lock(stackMutex);
        s.push(std::move(x));
    }
private:
    std::stack<int> s;
    std::mutex stackMutex;
};

int main()
{

}
