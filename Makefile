CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS =  chaineMain.o reseauMain.o ArbreQuatMain.o hachageMain.o

.PHONY:	all clean

all: $(PROGRAMS)

chaineMain.o: chaineMain.c chaine.o SVGwriter.o
	$(CC) -o chaineMain.o $(CFLAGS) chaineMain.c chaine.o SVGwriter.o -lm

reseauMain.o : reseau.o chaine.o SVGwriter.o reseauMain.c 
	$(CC) -o $@ $(CFLAGS) $^ -lm

ArbreQuatMain.o: ArbreQuat.o chaine.o reseau.o SVGwriter.o ArbreQuatMain.c 
	$(CC) -o $@ $(CFLAGS) $^ -lm

ArbreQuat.o: ArbreQuat.c
	$(CC) -c $(CFLAGS) ArbreQuat.c -lm

chaine.o: chaine.c
	$(CC) -c $(CFLAGS) chaine.c -lm

reseau.o : reseau.c
	$(CC) -c $(CFLAGS) $^ -lm

Hachage.o : Hachage.c
	$(CC) -c $(CFLAGS) $^ -lm

hachageMain.o : Hachage.o reseau.o SVGwriter.o chaine.o hachageMain.c
	$(CC) -o $@ $(CFLAGS) $^ -lm

SVGwriter.o: SVGwriter.c SVGwriter.h
	$(CC) -c $(CFLAGS) SVGwriter.c

clean:
	rm -f *.o *.html *~ $(PROGRAMS)
