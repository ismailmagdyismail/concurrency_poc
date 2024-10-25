# Description
a simple POCs for different aspects of concurrency management

# POCs
- casting.cpp: demonstrate type casting at caller / creator of thread to avoid dangling ptr
- danglingPtr.cpp: demenostrate dangling ptrs when detatching threads , having access by reference to an external variable
- raceCondition.cpp: simple race conditions , locking to solve it & synchornize access from muiltple threads
- RAII.cpp : demonstarte a wrapper around threads to automatically handle joining for threads in desctructor
- ThreadSafeStack.cpp : a wrapper around stack to provide a thread safe interface
- ThreadSafeStack2.cpp : another way to change stack interface to be thread safe

# How to run
- `source env.bash`
- run the following script `compile_run filename.cpp`
