#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    thread t([] {
        cout << "Thread is running" << endl;
    });

    t.detach(); // Detach the thread

    // Give some time for the detached thread to finish before main exits
    this_thread::sleep_for(chrono::seconds(1));

    cout << "Main thread is exiting" << endl;
    return 0;
}
