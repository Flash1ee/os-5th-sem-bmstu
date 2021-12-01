#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("CHILD PROCESS %s EXEC PROGRAM %s\n", argv[1], argv[0]);
    printf("Hello, world!\n");
    printf("I am a task that is executed using exec\n");
    printf("CHILD PROCESS %s COMPLETE EXEC PROGRAM %s\n", argv[1], argv[0]);
    printf("\n");

    return 0;
}
