#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <map>
#include <unistd.h>
#include <vector>

/**
 - reader writer problem
 - dns cacher , where cache is read way more frequently than written to
*/

class DNSCache
{
public:
    std::string readEntry(const std::string& entryName)
    {
        std::shared_lock<std::shared_mutex> sharedLock (rwMutex);
        if(entries.find(entryName) != entries.end()){
            return entries[entryName];
        }
        return "";
    }
    void updateEntry(const std::string& entryName, const std::string& entryValue)
    {
        std::lock_guard<std::shared_mutex>execlusiveLock(rwMutex);
        entries[entryName] = entryValue;
    }
private:
    std::shared_mutex rwMutex;
    std::map<std::string,std::string> entries;
};


DNSCache DNS_CACHE;
void readerThread(std::string entryToRead)
{
    while (true)
    {
        std::cout<<"[Reader]: "<< std::this_thread::get_id()<<" Reading entry "<<entryToRead<<'\n';
        std::cout<<"[Reader]: "<< DNS_CACHE.readEntry(entryToRead)<<'\n';
        sleep(2);
    }
}

void writerThread(std::string entryName,std::string entryValue)
{
    while (true)
    {
        std::cout<<"[Writer]: "<< std::this_thread::get_id()<<" Entries to be written "<<entryValue << " "<<entryValue <<'\n';
        DNS_CACHE.updateEntry(entryName, entryValue);
        sleep(5);
    }

}

int main()
{
    std::vector<std::thread>readers(2);
    std::vector<std::thread>writers(2);

    for(int i = 0 ; i < readers.size();i++)
    {
        readers[i] = std::thread(readerThread,std::to_string(i));
    }

    for(int i = 0 ; i<writers.size();i++)
    {
        writers[i] = std::thread(writerThread,std::to_string(i),std::string("ismail") + std::to_string(i));
    }

    for(int i = 0 ; i<readers.size();i++)
    {
        if(readers[i].joinable())
        {
            readers[i].join();
        }
    }
}
