#ifndef __CHAINE_H__
#define __CHAINE_H__	
#include<stdio.h>
#include<stdlib.h>

/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

Chaines* lectureChaines(FILE *f);
// Chaines* lectureChaines2(FILE *f); // On construire de facon recursive
CellPoint* creerCellPointRec(int nb, FILE* f);
CellChaine* creerCellChaineRec(int nb, FILE* f);
void libererCellPointRec(CellPoint* p);
void libererCellChaineRec(CellChaine* ch);
void ecrireChaines(Chaines *C, FILE *f);
void afficheChainesSVG(Chaines *C, char* nomInstance);
double distancePoints(CellPoint* p1, CellPoint* p2);
double longueurChaine(CellChaine* c);
double longueurTotale(Chaines *C);
int comptePointsTotal(Chaines *C);
extern void liberer_cell_point(CellPoint *cellP);
extern void liberer_cell_chaine(CellChaine *cellC);
extern void liberer_chaines(Chaines *C);

#endif	