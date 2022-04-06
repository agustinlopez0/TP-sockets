# gcc -c sockets.c
# gcc -o main main.c sockets.o
# ./main

all: program

program: server.c client.c  sockets.c sockets.h sockets.o db.txt
	gcc -o server server.c sockets.o
	gcc -o client client.c sockets.o

sockets.o:
	gcc -c sockets.c

clean:
	rm *.o *.exe server client