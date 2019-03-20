CC = g++
CFLAGS = -std=gnu++98 -Wall -Werror -pedantic
code: sortLines.o
	$(CC) $(CFLAGS) -o sortLines sortLines.o
code.o: sortLines.cpp
	$(CC) $(CFLAGS) -c sortLines.cpp
.PHONY:clean
	rm -f sortLines *.cpp~ *.h~



