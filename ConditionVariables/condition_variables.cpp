/*
Few important points to remember while using "condition variables" are as follows:
1. Condition variables allow us to synchronise threads via notifications.
   a. notify_one();
   b. notify_all();
2. You need mutex to use condition variable
3. Condition variable is used to synchronise two or more threads.
4. Best use case of condition variable is Producer/Consumer problem.
5. Condition variables can be used for two purposes:
    a. Notify other threads
    b. Wait for some condition
*/

//Example: Using condition_variable for addMoney and withdrawMoney scenario
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

mutex mtx;
condition_variable cv;
int balance = 0;
const int withdraw_amount = 1000;
const int deposit_amount = 2000;
bool ready_to_withdraw = false;

void addMoney() {
    this_thread::sleep_for(chrono::seconds(1)); // Simulate some delay
    unique_lock<mutex> lock(mtx);
    balance += deposit_amount;
    cout << "Added money: " << deposit_amount << ", New Balance: " << balance << endl;
    ready_to_withdraw = true;
    cv.notify_one(); // Notify one waiting thread
}

void withdrawMoney() {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, [] { return ready_to_withdraw; }); // Wait until notified and condition is met
    if (balance >= withdraw_amount) {
        balance -= withdraw_amount;
        cout << "Withdrew money: " << withdraw_amount << ", New Balance: " << balance << endl;
    } else {
        cout << "Insufficient balance to withdraw: " << withdraw_amount << endl;
    }
}

int main() {
    thread t1(withdrawMoney);
    thread t2(addMoney);

    t1.join();
    t2.join();

    return 0;
}
