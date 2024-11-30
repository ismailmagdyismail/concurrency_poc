#include <thread>
#include <unistd.h>
#include <functional>
#include <iostream>

/*
    - dangling ptr scenario cause x gets deleted , where thread is still threading , holding a reference to that variable
*/
void danglingPtr()
{
    int* x = new int(10);
    std::thread t = std::thread([&](){
        sleep(1);
        std::cout<<x<<'\n';
        std::cout<<*x<<'\n';
    });
    t.detach();
    x = 0;
    x = NULL;
    delete x;
}

void danglingPtr2()
{
    int* x = new int(10);
    std::thread t = std::thread([&](){
        sleep(1);
        std::cout<<x<<'\n';
        std::cout<<*x<<'\n';
    });
    x = 0;
    x = NULL;
    delete x;
    t.detach();
}
int main()
{
    danglingPtr();
    danglingPtr2();
    sleep(3);
}
