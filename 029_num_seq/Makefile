CFLAGS=-std=gnu99 -Wall -Werror -pedantic
step1: step1.o
	gcc $(CFLAGS) -o step1 step1.o
step1.o: step1.c
	gcc $(CFLAGS) -c step1.c
step2: step2.o
	gcc $(CFLAGS) -o step2 step2.o
step2.o: step2.c
	gcc $(CFLAGS) -c step2.c
step3: step3.o
	gcc $(CFLAGS) -o step3 step3.o
step3.o: step3.c
	gcc $(CGLAGS) -c step3.c
.PHONY: clean
clean:
	rm -f step1 *.o *.c~ *.h~
