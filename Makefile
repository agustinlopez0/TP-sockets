# gcc -c sockets.c
# gcc -o main main.c sockets.o
# ./main

all: program

program: main.c sockets.c sockets.h sockets.o
	gcc -o main main.c sockets.o

sockets.o:
	gcc -c sockets.c