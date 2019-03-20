CFLAGS=-ggdb3 -Wall -Werror -std=gnu99 -pedantic
Assign37: maxSeq.o test-subseq.o
	gcc $(CFLAGS) -o Assign37 maxSeq.o test-subseq.o
maxSeq.o: maxSeq.c
	gcc $(CFLAGS) -c maxSeq.c
test-subseq.o: test-subseq.c
	gcc $(CFLAGS) -c test-subseq.c
.PHONY: clean
clean:
	rm -f maxSeq *.o *.c~ *.h~
