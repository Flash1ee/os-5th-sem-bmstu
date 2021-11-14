CFILES   = $(wildcard *.c)
OBJFILES = $(CFILES:.c=.o)
EXECUTABLE = task_1 task_2

CC      = gcc
CFLAGS  = -Wall

.PHONY: clean task_1 task_2


task_1: task_01.o
	$(CC) $(CFLAGS) -o $@ $^

task_2: task_02.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(OBJFILES) $(OUT) $(EXECUTABLE)
