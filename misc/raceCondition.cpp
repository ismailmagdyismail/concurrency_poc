#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

/**
Run[1]:
[Excpeceted]: 100
[Actual]: 100%
*/


/**
Run[2]: race condition happend
raceCondition.exe(41244,0x16b40b000) malloc: *** error for object 0x60000075bfec: pointer being freed was not allocated
raceCondition.exe(41244,0x16b40b000) malloc: *** set a breakpoint in malloc_error_break to debug
due to accessing memory already freed for example , since vectors are always being resized
*/


void raceCondition()
{
    int threadsCount = 10;
    int iterations = 10;
    std::vector<int> v;
    std::vector<std::thread>threads(threadsCount);
    for(auto& thread : threads)
    {
        thread = std::thread([&]()->void{
            for(int i = 0 ;i<iterations;i++){
                v.push_back(1);
            }
        });
    }
    for(auto& thread : threads)
    {
        thread.join();
    }
    std::cout<<"[Excpeceted]: "<< iterations * threadsCount<<'\n';
    std::cout<<"[Actual]: "<<v.size();
}



void safe()
{
    int threadsCount = 10;
    int iterations = 10;
    std::mutex mux;
    std::vector<int> v;
    std::vector<std::thread>threads(threadsCount);
    for(auto& thread : threads)
    {
        thread = std::thread([&]()->void{
            for(int i = 0 ;i<iterations;i++){
                std::lock_guard<std::mutex> lock(mux);
                v.push_back(1);
            }
        });
    }
    for(auto& thread : threads)
    {
        thread.join();
    }
    std::cout<<"[Excpeceted]: "<< iterations * threadsCount<<'\n';
    std::cout<<"[Actual]: "<<v.size();
}


int main()
{
    safe();
}
