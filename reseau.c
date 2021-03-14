#include "Reseau.h"
#include <math.h>
#include <assert.h>
#define DOUBLE_PRECISION 0.00001

// a tester
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    int i;
    CellNoeud* cellnoeud = R->noeuds;
    Noeud* noeud = NULL;
    for (i = 0; i < R->nbNoeuds; i++, cellnoeud = cellnoeud->suiv)
    {
        noeud = cellnoeud->nd;
        if(fabs(noeud->x - x) < DOUBLE_PRECISION && fabs(noeud->y - y) < DOUBLE_PRECISION){
            return noeud;
        }
    }

    // creation d'un nouveau noeud et ajout dans le reseau
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

CellNoeud* ajouterVoisin(CellNoeud* prev, CellNoeud* next){
    assert(prev && prev->nd);
    if(!next) return NULL;
    // CellNoeud* cellN = (CellNoeud*) calloc(1, sizeof(CellNoeud));
    // CellNoeud* cellV = (CellNoeud*) calloc(1, sizeof(CellNoeud));
    CellNoeud* voisinTmp = next->nd->voisins;
    CellNoeud* voisinTmp2 = prev->nd->voisins;
    next->nd->voisins = prev;
    prev->nd->voisins = 

    prev->nd->voisins = next;
    next->voisins = prevC->nd->voisins;
    prevC->nd->voisins = cellN;

    prevC-> = cellN;

    return cellN;
}

CellCommodite* creerCellCommodite(Noeud* extrA, Noeud* extrB, CellCommodite* suiv){
    CellCommodite* res = (CellCommodite*) calloc(1, sizeof(CellCommodite));
    res->extrA = extrA;
    res->extrB = extrB;
    res->suiv = suiv;
    return res;
}

Reseau* reconstitueReseauListe(Chaines *C){

    int i;
    Reseau* reso = (Reseau*) calloc(1, sizeof(Reseau));
    reso->gamma = C->gamma;

    CellChaine* chaineTmp = C->chaines;
    CellPoint* pointTmp = NULL;
    CellPoint* pointPrev = NULL;
    CellPoint* pointTete = NULL;
    Noeud* noeudTmp = NULL;
    Noeud* noeudTete = NULL;
    Noeud* noeudFin = NULL;
    CellNoeud* cndPrev = NULL;
    CellNoeud* cndTmp = NULL;
    CellCommodite* commoditeTmp = NULL;
    // On parcourt une `a une chaque cha^ıne:
    
    for ( i = 0; i < C->nbChaines; i++, chaineTmp = chaineTmp->suiv)
    {
        // si Chaines est bien construit, les deux assert ne pose pas de probleme
        // si chaineTmp == NULL, on a mal compte le nombre de chaines
        assert(chaineTmp);

        pointTete = chaineTmp->points;// on fait hypothese que ce n'est pas NULL
        pointTmp = pointTete;
        noeudTete = rechercheCreeNoeudListe(reso, pointTmp->x, pointTmp->y);
        pointPrev = pointTmp;
        pointTmp = pointTmp->suiv;

        // Pour chaque point p de la cha^ıne:
        while(pointTmp){
            // Si p !∈ V (on teste si le point n’a pas d´ej`a ´et´e rencontr´e auparavant)
                // On ajoute dans V un nœud correspond au point p.
            noeudTmp = rechercheCreeNoeudListe(reso, pointTmp->x, pointTmp->y);
            
            // On met `a jour la liste des voisins de p et celles de ses voisins.
            // Junji : Je sais pas comment faire, faut demander au prof
            // car si on creer on a que Noeud, mais liste de voisins a besoin de CellNoeud
            // si on en creer, il y aurait plusieur CellNoeud dont nd pointe vers le meme Noeud
            ajouterVoisin(noeudTmp, );

            // passe au point suivant
            pointPrev = pointTmp;
            pointTmp = pointTmp->suiv;
        }
        
            
            
        // On conserve la commodit´e de la cha^ıne.
        assert(noeudTete && noeudTmp);
        commoditeTmp = creerCellCommodite(noeudTete, noeudTmp, commoditeTmp);
    }
    // si chaineTmp == NULL, on a mal compte le nombre de chaines
    assert(!chaineTmp);

    reso->commodites = commoditeTmp;

    return reso;
}

