CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS =  chaineMain.o reseauMain.o

.PHONY:	all clean

all: $(PROGRAMS)

chaineMain.o: chaineMain.c chaine.o SVGwriter.o
	$(CC) -o chaineMain.o $(CFLAGS) chaineMain.c chaine.o -lm

chaine.o: chaine.c SVGwriter.o
	$(CC) -c -o chaine.o $(CFLAGS) chaine.c -lm

SVGwriter.o: SVGwriter.c
	$(CC) -c -o SVGwriter.o $(CFLAGS) SVGwriter.c

reseauMain.o:

reseau.o:

clean:
	rm -f *.o *~ $(PROGRAMS)
