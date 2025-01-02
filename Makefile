all: tests

CFLAGS += -g -Wall 

tests: main.c
	gcc $(CFLAGS) -o tests main.c

clean:
	rm -f *~ *.o 