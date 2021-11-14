#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    const int n = 2;
    int child_processes[n];

    printf("PARENT BEFORE FORK -- PID: %d GROUP PID: %d\n", getpid(), getpgrp());

    for (int i = 0; i < n; i++) {
        child_processes[i] = fork();

        if (child_processes[i] == -1) {
            printf("Can't fork\n");
            return EXIT_FAILURE;
        }

        if (child_processes[i] == 0) {
            sleep(2);
            printf("CHILD %d -- PID: %d PARENT PID: %d GROUP PID: %d\n", i + 1, \
                    getpid(), getppid(), getpgrp());

            return EXIT_SUCCESS;
        }
    }
    for (int i = 0; i < n; i++) {
        int status;

        pid_t child = wait(&status);
        if (WIFEXITED(status)) {
            printf("CHILD PROCESS WITH PID = %d EXITED WITH CODE %d\n", child, WEXITSTATUS(status));

        } else {
            printf("CHILD WITH PID = %d PROCESS EXITED UBNORMALLY\n", child);
        }
    }
    printf("PARENT AFTER FORK -- PID: %d GROUP PID: %d CHILDS 1: %d CHILD 2: %d\n", \
            getpid(), getpgrp(), child_processes[0], child_processes[1]);

    return EXIT_SUCCESS;
}