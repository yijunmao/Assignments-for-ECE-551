CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic
myProgram: test-power.o power.o
	gcc $(CFLAGS) -o myProgram test-power.o power.o
test-power.o: test-power.c
	gcc $(CFLAGS) -c test-power.c
power.o: power.c
	gcc $(CFLAGS) -c power.c
