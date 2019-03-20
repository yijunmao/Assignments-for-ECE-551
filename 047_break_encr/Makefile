CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic
breaker: breaker.o
	gcc $(CFLAGS) -o breaker breaker.o
breaker.o: breaker.c
	gcc $(CFLAGS) -c breaker.c
./PHONY: clean
clean:
	rm -f breaker *.o *.c~ *.h~
