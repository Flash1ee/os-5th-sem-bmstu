CC = gcc
INC = inc
OBJ = $(wildcard *.c)
FLAGS = -Werror -Wall -Wpedantic -std=c99

a.out:
	${CC} ${OBJ} -I${INC} ${FLAGS}

clean:
	rm *.o *.exe *.out

run: a.out
	./a.out