CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS =  chaineMain.o

.PHONY:	all clean

all: $(PROGRAMS)

chaineMain.o: chaineMain.c chaine.o
	$(CC) -o chaineMain.o $(CFLAGS) chaineMain.c chaine.o -lm

chaine.o: chaine.c SVGwriter.o
	$(CC) -c -o chaine.o $(CFLAGS) chaine.c -lm

SVGwriter.o: SVGwriter.c
	$(CC) -c -o SVGwriter.o $(CFLAGS) SVGwriter.c

clean:
	rm -f *.o *~ $(PROGRAMS)
