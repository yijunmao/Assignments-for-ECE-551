CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic
mystat: mystat.o
	gcc $(CFLAGS) -o mystat mystat.o
mystat.o: mystat.c
	gcc $(CFLAGS) -c mystat.c
./PHONY:clean
clean:
	rm -f mystat *.o *.c~ *.h~
