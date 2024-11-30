#include <thread>
#include <iostream>

class RAIIThread
{
public:
    RAIIThread(std::thread&& thread) : t(std::move(thread)) {
        std::cout << "MOVE\n";
    }
    RAIIThread(std::thread& thread) : t(std::move(thread)) {
        std::cout << "MOVE L VALUE\n";
    }

    RAIIThread(const RAIIThread& other) = delete;
    RAIIThread& operator=(const RAIIThread& other) = delete;

    ~RAIIThread() {
        if (t.joinable()) {
            t.join();
        }
    }

private:
    std::thread t;
};

void raiiThread() {
    RAIIThread raiiThread(std::thread([]() {
        std::cout << "Thread is running\n";
    }));

    std::thread t = std::thread([](){
        std::cout<<"L Value thread\n";
    });
    RAIIThread raii2(t);
}

int main() {
    raiiThread();
}
