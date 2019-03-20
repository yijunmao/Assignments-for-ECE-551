CC = g++
CFLAGS = -std=gnu++98 -Wall -Werror -pedantic
code: code.o
	$(CC) $(CFLAGS) -o code code.o
code.o: code.cpp
	$(CC) $(CFLAGS) -c code.cpp
.PHONY:clean
	rm -f code *.o

