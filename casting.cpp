#include <algorithm>
#include <cstddef>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <utility>



void f(int i,std::string const& s){
    std::cout<<"[THread]: "<<i<<" "<<s<<std::endl<<'\n';
}

/**
    - no problems here since type casting is done at called,  not thread context : so all vars are still valid
*/
void safe()
{
    char buffer[1024] = "buffer";
    std::thread t(f,3,std::string(buffer));
    t.detach();
}


/**
    - PROBLEM: type casting happens at thread which may execute after unsafe gets pooped,  so ref to buffer is invalid
*/
void unsafe()
{
    char buffer[1024] = "buffer";
    std::thread t(f,3,buffer);
    t.detach();
}

int main()
{
    std::cout<<std::thread::hardware_concurrency();
    safe();
    sleep(2);
}
