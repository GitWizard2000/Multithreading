#include <iostream>
#include <thread>

using namespace std;

void function(int *num)
{
    int sum=0;
    for(int i=0; i<*num; i++)
    {
        sum = sum + i;
    }
    std::cout << "Summation: "<<sum<< std::endl;
}

int main()
{
    int a = 200;
    int b = 200;
    std::cout << "Hey Ram!" << std::endl;
    std::thread t1(function, &a);
    std::thread t2(function, &b);

    // function(200);
    // function(100);
    // t1.detach();
    // t2.detach();
    t1.join();
    t2.join();

    return 0;
}
