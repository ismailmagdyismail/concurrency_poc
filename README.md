# Description
a simple POCs for different aspects of concurrency management

# POCs
- casting.cpp: demonstrate type casting at caller / creator of thread to avoid dangling ptr
- danglingPtr.cpp: demenostrate dangling ptrs when detatching threads , having access by reference to an external variable
- raceCondition.cpp: simple race conditions , locking to solve it & synchornize access from muiltple threads
- RAII.cpp : demonstarte a wrapper around threads to automatically handle joining for threads in desctructor
- ThreadSafeStack.cpp : a wrapper around stack to provide a thread safe interface
- ThreadSafeStack2.cpp : another way to change stack interface to be thread safe
- DNSCache.cpp : demonstrates reader-writer problem , solving it using shared mutex
- hierarchalMutex.cpp : demonstrates heirarchal mutex strategy to always enforce in-order locking at run-time to AVOID DEADLOCKS
- parallelAccumlate.cpp : SIMD solution to summing up vector
- Router_INH : simulate n threads of devices reading and writing from Router , and BUSY waiting to handle limited connections using inherteince and busy waiting
- Router_Compoistion_Condition_vars : utilizes composition over inherteince , use condition variables to avoid busy waiting
- Router_Thread_Pools : poc of thread pools
- Procuder_consumer: poc of thread safe queue , with blocking & non-blocking operations and producer consumer problem


# How to run
- `source env.bash`
- run the following script `run filename.cpp` for single/standalone files
