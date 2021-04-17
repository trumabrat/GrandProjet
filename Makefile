CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS =  chaineMain.o reseauMain.o ArbreQuatMain.o hachageMain.o comparaisonsMain.o troisInstancesMain.o grapheMain.o

.PHONY:	all clean

all: $(PROGRAMS)

grapheMain.o : grapheMain.c Graphe.o chaine.o reseau.o SVGwriter.o ArbreQuat.o Struct_File.o Struct_Liste.o 
	$(CC) -o $@ $(CFLAGS) $^ -lm

comparaisonsMain.o : comparaisonsMain.c comparaisons.o chaine.o reseau.o Hachage.o ArbreQuat.o SVGwriter.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

troisInstancesMain.o : troisInstancesMain.c comparaisons.o chaine.o reseau.o Hachage.o ArbreQuat.o SVGwriter.o
	$(CC) -o $@ $(CFLAGS) $^ -lm

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

comparaisons.o : comparaisons.c
	$(CC) -c $(CFLAGS) $^ -lm

Graphe.o : Graphe.c
	$(CC) -c $(CFLAGS) $^

Struct_File.o : Struct_File.c
	$(CC) -c $(CFLAGS) $^

Struct_Liste.o : Struct_Liste.c
	$(CC) -c $(CFLAGS) $^

SVGwriter.o: SVGwriter.c SVGwriter.h
	$(CC) -c $(CFLAGS) SVGwriter.c

clean:
	rm -f *.o *.html *~ $(PROGRAMS)
