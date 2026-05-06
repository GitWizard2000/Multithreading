//TOPIC: Atomic Operations in C++
/*
NOTES:
1. Atomic operations are indivisible operations that are guaranteed to be thread-safe without the need for locks.
2. The C++ Standard Library provides the <atomic> header which defines atomic types and operations.
3. Atomic types include std::atomic<T> where T can be any trivially copyable type, such as int, bool, pointers, etc.
4. Atomic operations include load, store, exchange, compare-and-swap, and fetch-and-add among others.
5. Using atomic operations can help avoid race conditions and ensure data integrity when multiple threads access shared resources.
*/

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> counter (0); // Shared atomic counter initialized to 0

void increment() {
    for (int i = 0; i < 1000; ++i) {
        counter.fetch_add(1);  // atomic increment
    }
}

int main() {
    std::thread t1(increment), t2(increment);
    t1.join(); t2.join();
    std::cout << "Counter: " << counter.load() << "\n";
}
