#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define LENBUF 64
const char* message[] = {"dlkbnvlcm", "kfdsnbb ,fkegj"};

int main(int argc, char* argv[]) {
    const int n = 2;
    int child_processes[n];

    char buf[strlen(message[0]) + strlen(message[1]) + 2];

    int fd[2];
    int p = pipe(fd);
    if (p == -1) {
        printf("Can not create pipe\n");
        return EXIT_FAILURE;
    }

    printf("PARENT BEFORE FORK -- PID: %d GROUP PID: %d\n\n", getpid(), getpgrp());

    for (int i = 0; i < n; i++) {
        child_processes[i] = fork();

         if (child_processes[i] == -1) {
            printf("Can't fork\n");
            exit(EXIT_FAILURE);
        }

        if (child_processes[i] == 0) {
            printf("CHILD %d -- PID: %d PARENT PID: %d GROUP PID: %d\n", i + 1, \
                    getpid(), getppid(), getpgrp());

            close(fd[0]);
            write(fd[1], message[i], strlen(message[i]) + 1);

            printf("CHILD %d WITH PID %d send message %s\n\n\n", i+1, getpid(), message[i]);

            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < n; i++) {
        int status;

        pid_t child = wait(&status);
        if (WIFEXITED(status)) {
            printf("CHILD PROCESS FINISHED NORMALLY.\n");
            printf("CHILD PID = %d EXITED WITH CODE %d\n", child, WEXITSTATUS(status));
            printf("\n");
        } else {
            printf("CHILD PROCESS TERMINATED WITH UN - INTERCEPTED SIGNAL.\n");
            printf("CHILD PID = %d, TERMINATION CODE = %d\n", child, WEXITSTATUS(status));
            printf("\n");
        }
    }

    printf("PARENT AFTER FORK -- PID: %d GROUP PID: %d CHILDS 1: %d CHILD 2: %d\n\n", \
            getpid(), getpgrp(), child_processes[0], child_processes[1]);
    
    close(fd[1]);
    int cur_len = 0;
    for (int i = 0; i < n; i++) {
        cur_len += strlen(message[i]) + 1;
        read(fd[0], buf, cur_len);
        printf("Message %d - %s\n", i + 1, buf);
    }
    printf("\n");

    printf("Child's PID processes which received message with pipe %d %d\n", 
            child_processes[0], child_processes[1]);

    return EXIT_SUCCESS;
}