CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic
test: test.o
	gcc $(CFLAGS) -o test test.o
test.o: test.c
	gcc $(CFLAGS) -c test.c
.PHONY: clean
clean:
	rm -f test *.o *.c~ *.h~
