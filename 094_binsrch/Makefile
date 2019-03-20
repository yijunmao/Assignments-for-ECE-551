CFLAGS= -Wall -Werror -std=gnu++98 -pedantic -ggdb3


test: test-bsearch.cpp function.h
	g++ $(CFLAGS) -o test test-bsearch.cpp

test-bsearch.cpp: bsearch.cpp
	g++ $(CFLAGS) -o 

clean:
	rm -f test *~
