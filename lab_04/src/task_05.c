#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define SLEEP 2

#define LENBUF 64
const char* message[] = {"dlkbnvlcm", "kfdsnbb ,fkegj"};
int fd[2];
int i = 0;

int flag = 0;

void sig_processing() {
    flag = 1;
}

int main(int argc, char* argv[]) {
    const int n = 2;
    int child_processes[n];

    char buf[LENBUF];

    int p = pipe(fd);
    if (p == -1) {
        printf("Can not create pipe\n");
        return EXIT_FAILURE;
    }

    printf("PARENT BEFORE FORK -- PID: %d GROUP PID: %d\n\n", getpid(), getpgrp());
    signal(SIGTSTP, sig_processing);

    for (int i = 0; i < n; i++) {
        child_processes[i] = fork();

         if (child_processes[i] == -1) {
            printf("Can't fork\n");
            exit(EXIT_FAILURE);
        }

        if (child_processes[i] == 0) {
            sleep(2);
            if (flag) {
                close(fd[0]);

                write(fd[1], message[i], strlen(message[i]) + 1);
                printf("CHILD %d -- PID: %d PARENT PID: %d GROUP PID: %d\n", i + 1, \
                    getpid(), getppid(), getpgrp());
                exit(EXIT_SUCCESS);
            }
        }
    }
    printf("\n");
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
    
    sleep(2);

    close(fd[1]);
    for (int i = 0; i < n; i++) {
        read(fd[0], buf, strlen(message[i]) + 1);
        printf("Message %d - %s\n", i + 1, buf);
    }
    printf("\n");

    printf("PARENT id = %d child_1 pid = %d child_2 pid = %d\n", getpid(),
            child_processes[0], child_processes[1]);


    return EXIT_SUCCESS;
}