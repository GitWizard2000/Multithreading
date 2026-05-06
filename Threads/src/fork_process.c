#include <stdio.h>
#include <unistd.h>
#include <sched.h>

int main() {
    int x = 5;
    pid_t pid = fork();

    if (pid == 0) {
        x += 5;
        printf("Child: x = %d\n", x);
    } else {
        printf("Parent: x = %d\n", x);
    }

    return 0;
}