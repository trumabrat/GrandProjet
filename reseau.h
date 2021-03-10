#include "Reseau.h"
#include <math.h>

// a tester
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    int i;
    CellNoeud* cellnoeud = R->noeuds;
    Noeud* noeud = NULL;
    for (i = 0; i < R->nbNoeuds; i++, cellnoeud = cellnoeud->suiv)
    {
        noeud = cellnoeud->nd;
        if(fabs(noeud->x - x) < 0.00001 && fabs(noeud->y - y) < 0.00001){
            return noeud;
        }
    }
    Noeud* newNoeud = creerNoeud(++R->nbNoeuds, x, y);
    CellNoeud* newCellNoeud = (CellNoeud*) calloc(1, sizeof(CellNoeud));
    newCellNoeud->nd = newNoeud;
    newCellNoeud->suiv = R->noeuds;
    R->noeuds = newCellNoeud;
    return newNoeud;
}

// creer un Noeud
Noeud* creerNoeud(int num, double x, double y){
    Noeud* res = (Noeud*) calloc(1, sizeof(Noeud));
    res->num = num;
    res->x = x;
    res->y = y;
    return res;
}

// int comparer_ordonnees(double x1, double y1, double x2, double y2){
//     return fabs(x1 - x2) < 0.00001 && fabs(y1 - y2) < 0.00001;
// }

Reseau* reconstitueReseauListe(Chaines *C);

