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
            exit(EXIT_FAILURE);
        }

        if (child_processes[i] == 0) {
            sleep(1);
            printf("CHILD %d -- PID: %d PARENT PID: %d GROUP PID: %d\n", i + 1, \
                    getpid(), getppid(), getpgrp());
            if (i == n - 1) {
                printf("\n");
            }
            exit(EXIT_SUCCESS);
        }
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        int status;

        pid_t child = wait(&status);
        printf ("childpid: %d stat_loc: %d \n" , child, status);
        if (WIFEXITED(status)) {
            printf("Child - process finished normally.\n");
            printf("CHILD PROCESS WITH PID = %d EXITED WITH CODE %d\n", child, WEXITSTATUS(status));
            printf("\n");
        } else {
            printf("Child - process terminates with un - intercepted signal.\n");
            printf("CHILD WITH PID = %d, TERMINATION CODE = %d\n", child, WEXITSTATUS(status));
            printf("\n");
        }
    }
    printf("PARENT AFTER FORK -- PID: %d GROUP PID: %d CHILDS 1: %d CHILD 2: %d\n", \
            getpid(), getpgrp(), child_processes[0], child_processes[1]);
    printf("PARENT - PROCESS FINISHED.\n");

    return EXIT_SUCCESS;
}