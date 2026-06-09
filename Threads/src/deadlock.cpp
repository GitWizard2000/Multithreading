//Basic example of deadlock in C++
// Note: This code may lead to a deadlock situation where both threads are waiting for each other to release the locks.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
mutex mtx1;
mutex mtx2;

void thread1_func() {
    lock_guard<mutex> lock1(mtx1);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate some work
    lock_guard<mutex> lock2(mtx2);
    cout << "Thread 1 acquired both locks." << endl;
}

void thread2_func() {
    lock_guard<mutex> lock2(mtx2);
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate some work
    lock_guard<mutex> lock1(mtx1);
    cout << "Thread 2 acquired both locks." << endl;
}

int main() {
    thread t1(thread1_func);
    thread t2(thread2_func);

    t1.join();
    t2.join();

    cout << "Both threads completed." << endl;
    return 0;
}
