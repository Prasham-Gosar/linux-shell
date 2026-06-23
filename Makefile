CC = gcc
CFLAGS = -Wall -g

shell: shell.o parser.o builtins.o executor.o
	gcc -o shell shell.o parser.o builtins.o executor.o

shell.o: shell.c shell.h
	gcc $(CFLAGS) -c shell.c

parser.o: parser.c shell.h
	gcc $(CFLAGS) -c parser.c

builtins.o: builtins.c shell.h
	gcc $(CFLAGS) -c builtins.c

executor.o: executor.c shell.h
	gcc $(CFLAGS) -c executor.c

clean:
	rm -f *.o shell