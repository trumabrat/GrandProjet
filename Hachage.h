#ifndef HACHAGE_H
#define HACHAGE_H
#include "Reseau.h"
typedef struct _tablehachage{
    int taille;
    CellNoeud** tableHachageNoeud;
} TableHachage;

double fonctionCle(double x, double y);
int fonctionHachage(double k, int nbCase);
TableHachage* creerTableHachage(int taille);
#endif