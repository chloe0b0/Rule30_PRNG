CC = gcc

all:
	PRNG

PRNG:
	$(CC) -o PRNG Rule30.c -O2 -finline-functions

clean:
	rm PRNG
