// This code show how producer consumer problem can be solved using mutex and condition variables

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

queue<int> buffer;
const int BUFFER_SIZE = 5;

mutex mtx;
condition_variable notFull;
condition_variable notEmpty;

void producer()
{
    for(int item = 1; item <= 20; item++)
    {
        unique_lock<mutex> lock(mtx);

        // Wait until buffer has space
        notFull.wait(lock, [] {
            return buffer.size() < BUFFER_SIZE;
        });

        buffer.push(item);

        cout << "Produced: " << item
             << " | Buffer Size: "
             << buffer.size() << endl;

        lock.unlock();

        notEmpty.notify_one();

        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer()
{
    for(int i = 1; i <= 20; i++)
    {
        unique_lock<mutex> lock(mtx);

        // Wait until buffer contains data
        notEmpty.wait(lock, [] {
            return !buffer.empty();
        });

        int item = buffer.front();
        buffer.pop();

        cout << "Consumed: " << item
             << " | Buffer Size: "
             << buffer.size() << endl;

        lock.unlock();

        notFull.notify_one();

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main()
{
    thread prod(producer);
    thread cons(consumer);

    prod.join();
    cons.join();

    return 0;
}
