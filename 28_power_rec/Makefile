CFLAGS=-Wall -Werror -pedantic -g

test-power:test-power.o power.o
	gcc -o test-power test-power.o power.o

test-power.o:test-power.c
	gcc $(CFLAGS) -c test-power.c

power.o:power.c
	gcc $(CFLAGS)  -c power.c 
