CC = gcc
CFLAGS = -Wall -std=c11
CFLAGS2 = -Wall -std=c11 -I$(INCLUDE) -c
INCLUDE = ./include

all: miniMinden


miniMinden: miniMinden.o 
	$(CC) $(CFLAGS) -o $@ $^
	
miniMinden.o: miniMinden.c
	$(CC) $(CFLAGS2) -o $@ $^

	

run: miniMinden
	./miniMinden
	
clean:
	rm -rf miniMinden
	rm -rf miniMinden.o
