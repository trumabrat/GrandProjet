#include "Hachage.h"
#include "Reseau.h"
#include <math.h>
#include <assert.h>
#define NBDOR (sqrt(5)-1)/2
#ifndef DOUBLE_PRECISION
#define DOUBLE_PRECISION 0.00001
#endif
// fonction pour generer la clef a partir de x,y
double fonctionCle(double x, double y){
    return (y+(x+y)*(x+y+1)/2);
}

// cela nous semble approprie car il y a peu de collision.
int fonctionHachage(double k, int nbCase){
    return (int) (nbCase*(k*NBDOR - (int)(k*NBDOR)));
}

// creer table de hachage
TableHachage* creerTableHachage(int taille){
    TableHachage* res = (TableHachage*) calloc(1, sizeof(TableHachage));
    assert(res);
    res->taille = taille;
    res->tableHachageNoeud = calloc(taille, sizeof(CellNoeud*));
    assert(res->tableHachageNoeud);
    return res;
}

Noeud* rechercheHachageNoeud(TableHachage* H, double x, double y){
    int indiceCase = fonctionHachage(fonctionCle(x, y), H->taille);
    CellNoeud* tmp = H->tableHachageNoeud[indiceCase];
    Noeud* nd = NULL;
    while(tmp){
        nd = tmp->nd;
        assert(nd); // pour securiser
        if(nd->x - x < DOUBLE_PRECISION && nd->y - y < DOUBLE_PRECISION){
            return nd;
        }
        tmp = tmp->suiv;
    }
    return NULL;
}

TableHachage* enregistrerHachage(TableHachage* H, Noeud* n){
    int indiceCase = fonctionHachage(fonctionCle(n->x, n->y), H->taille);
    CellNoeud* tmp = H->tableHachageNoeud[indiceCase];
    CellNoeud* newCN = creerCellNoeud(n, tmp);
    H->tableHachageNoeud[indiceCase] = newCN;
    return H;
}

// Noeud* rechercheCreeNoeudHachage(Reseau *R, TableHachage* H, double x, double y){
//     // recherche du noeud
//     int indiceCase = fonctionHachage(fonctionCle(x, y), H->taille);
//     CellNoeud* tmp = H->tableHachageNoeud[indiceCase];
//     CellNoeud* prev = NULL;
//     Noeud* nd = NULL;
//     while(tmp){
//         nd = tmp->nd;
//         assert(nd); // pour securiser
//         if(nd->x - x < DOUBLE_PRECISION && nd->y - y < DOUBLE_PRECISION){
//             return nd;
//         }
//         prev = tmp;
//         tmp = tmp->suiv;
//     }

//     // si c'est pas dans la table
//     // creation d'un nouveau noeud et ajout dans la table de hachage
//     Noeud* newNoeud = creerNoeud(++R->nbNoeuds, x, y);

//     if(prev && !tmp){
//         // prev c'est avant la fin de la table de hachage
//         prev->suiv = creerCellNoeud(newNoeud, NULL);
//     }else{// c'est une case vide
//         // mettre a jour le table de hachage
//         H->tableHachageNoeud[indiceCase] = creerCellNoeud(newNoeud, H->tableHachageNoeud[indiceCase]);
//     }
//     // ajout dans le reseau
//     R->noeuds = creerCellNoeud(newNoeud, R->noeuds);
//     return newNoeud;
// }

Noeud* rechercheCreeNoeudHachage(Reseau *R, TableHachage* H, double x, double y){
    // recherche du noeud
    Noeud* nd = rechercheHachageNoeud(H, x, y);
    // si dans la table
    if(nd) return nd;

    // sinon creation d'un nouveau noeud et ajout dans la table de hachage
    Noeud* newNoeud = creerNoeud(++R->nbNoeuds, x, y);
    // // PROBLEM 
    int indiceCase = fonctionHachage(fonctionCle(x, y), H->taille);
    H->tableHachageNoeud[indiceCase] = creerCellNoeud(newNoeud, H->tableHachageNoeud[indiceCase]);

    // ajout dans le reseau
    R->noeuds = creerCellNoeud(newNoeud, R->noeuds);
    return newNoeud;
}

Reseau* reconstitueReseauHachage(Chaines *C, int M){
    int i;
    Reseau* reso = (Reseau*) calloc(1, sizeof(Reseau));
    reso->gamma = C->gamma;
    TableHachage* H = creerTableHachage(M);

    CellChaine* chaineTmp = C->chaines;
    CellPoint* pointTmp = NULL;
    CellPoint* pointPrev = NULL;
    CellPoint* pointTete = NULL;
    Noeud* noeudPrev = NULL;
    Noeud* noeudTmp = NULL;
    Noeud* noeudTete = NULL;
    CellCommodite* commoditeTmp = NULL;

    // On parcourt une `a une chaque cha^ıne:
    for ( i = 0; i < C->nbChaines; i++, chaineTmp = chaineTmp->suiv)
    {
        // si Chaines est bien construit, les deux assert ne pose pas de probleme
        // si chaineTmp == NULL, on a mal compte le nombre de chaines
        assert(chaineTmp);

        pointTete = chaineTmp->points;// on fait hypothese que ce n'est pas NULL
        pointTmp = pointTete;

        // On s'occupe du premier neoud
        noeudTete = rechercheCreeNoeudHachage(reso, H, pointTmp->x, pointTmp->y);
        noeudPrev = noeudTete;
        pointPrev = pointTmp;
        pointTmp = pointTmp->suiv;

        // Pour chaque point p de la cha^ıne:
        while(pointTmp){
            // Si p !∈ V (on teste si le point n’a pas d´ej`a ´et´e rencontr´e auparavant)
                // On ajoute dans V un nœud correspond au point p.
            noeudTmp = rechercheCreeNoeudHachage(reso, H, pointTmp->x, pointTmp->y);
            
            // On met `a jour la liste des voisins de p et celles de ses voisins.
            noeudPrev = ajouterVoisin(noeudPrev, noeudTmp);

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
