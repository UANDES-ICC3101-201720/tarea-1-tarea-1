CC=gcc
CFLAGS=-Wall

all: binsearch datagen

datagen: datagen.c 
	$(CC) -o datagen datagen.c $(CFLAGS) -lm

binsearch: binsearch.c util.o
	$(CC) -o binsearch binsearch.c util.o $(CFLAGS) -lm -pthread

util.o:
	$(CC) -c -o util.o util.c $(CFLAGS)

clean:
	rm datagen binsearch *.o