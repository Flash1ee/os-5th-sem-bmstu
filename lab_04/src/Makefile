CFILES   = $(wildcard *.c)
OBJFILES = $(CFILES:.c=.o)
EXECUTABLE = task_1 task_2 task_3 task_3_exec

CC      = gcc
CFLAGS  = -Wall

.PHONY: clean task_1 task_2 task_3


task_1: task_01.o
	$(CC) $(CFLAGS) -o $@ $^

task_2: task_02.o
	$(CC) $(CFLAGS) -o $@ $^

task_3: task_03.o task_03_exec.o
	$(CC) $(CFLAGS) -o $@ task_03.o
	$(CC) $(CFLAGS) -o task_3_exec task_03_exec.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJFILES) $(OUT) $(EXECUTABLE)
