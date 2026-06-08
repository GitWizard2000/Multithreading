#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <semaphore>
#include <chrono>

using namespace std;

queue<int> buffer;
const int BUFFER_SIZE = 5;

mutex mtx;

// Counting semaphores
counting_semaphore<BUFFER_SIZE> emptySlots(BUFFER_SIZE);
counting_semaphore<BUFFER_SIZE> fullSlots(0);

void producer()
{
    for(int item = 1; item <= 20; item++)
    {
        emptySlots.acquire();

        {
            lock_guard<mutex> lock(mtx);

            buffer.push(item);

            cout << "Produced: "
                 << item
                 << " | Buffer Size: "
                 << buffer.size()
                 << endl;
        }

        fullSlots.release();

        this_thread::sleep_for(
            chrono::milliseconds(500));
    }
}

void consumer()
{
    for(int i = 1; i <= 20; i++)
    {
        fullSlots.acquire();

        int item;

        {
            lock_guard<mutex> lock(mtx);

            item = buffer.front();
            buffer.pop();

            cout << "Consumed: "
                 << item
                 << " | Buffer Size: "
                 << buffer.size()
                 << endl;
        }

        emptySlots.release();

        this_thread::sleep_for(
            chrono::milliseconds(1000));
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
