#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const int n = 2;
    int child_processes[n];

    printf("PARENT BEFORE FORK -- PID: %d GROUP PID: %d\n", getpid(), getpgrp());

    for (int i = 0; i < n; i++) {
        child_processes[i] = fork();

        if (child_processes[i] == -1) {
            printf("Can't fork\n");
            exit(EXIT_FAILURE);
        }

        if (child_processes[i] == 0) {
            sleep(2);
            printf("\nCHILD %d -- PID: %d PARENT PID: %d GROUP PID: %d\n", i + 1, \
                    getpid(), getppid(), getpgrp());
            exit(EXIT_SUCCESS);
        }
    }

    printf("PARENT AFTER FORK -- PID: %d GROUP PID: %d CHILDS 1: %d CHILD 2: %d\n", \
            getpid(), getpgrp(), child_processes[0], child_processes[1]);
    printf("PARENT PROCESS FINISHED\n");

    return EXIT_SUCCESS;
}