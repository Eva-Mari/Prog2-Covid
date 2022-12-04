#

CFLAGS = -Wall -pedantic -g
OBJ = date.o list.o main.o
OBJ2 = test.o date.o list.o
OBJ3 = date.o stack.o main2.o
OBJ4 = teststack.o date.o stack.o
BIN = main.exe test.exe main2.exe teststack.exe

#
date.o: date.c date.h
	gcc $(CFLAGS) -c date.c -o date.o

list.o: list.c list.h date.h
	gcc $(CFLAGS) -c list.c -o list.o

stack.o: stack.c stack.h date.h
	gcc $(CFLAGS) -c stack.c -o stack.o

main.o: main.c date.h list.h
	gcc $(CFLAGS) -c main.c -o main.o

main2.o: main2.c date.h stack.h
	gcc $(CFLAGS) -c main2.c -o main2.o

#
main: date.o list.o main.o
	gcc $(CFLAGS) $(OBJ) -o main

main2: date.o stack.o main2.o
	gcc $(CFLAGS) $(OBJ3) -o main2

#Test

#
test.o: test.c list.h date.h
	gcc $(CFLAGS) -c test.c -o test.o

teststack.o: teststack.c stack.h date.h
	gcc $(CFLAGS) -c teststack.c -o teststack.o

#
test: test.o date.o list.o
	gcc $(CFLAGS) $(OBJ2) -o test

teststack: teststack.o date.o stack.o
	gcc $(CFLAGS) $(OBJ4) -o teststack

#runtest
runtest: test
	./test

runtest2: teststack
	./teststack

all: main test main2 teststack

clean:
	del $(BIN) $(OBJ) $(OBJ2) $(OBJ3) $(OBJ4)
