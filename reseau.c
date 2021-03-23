#include "Reseau.h"
#include "SVGwriter.h"
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


CellNoeud* ajouterVoisin(CellNoeud* prevC, Noeud* next){
    if(!next || !prevC) return NULL;
    assert(prevC->nd);
    CellNoeud* cellN = (CellNoeud*) calloc(1, sizeof(CellNoeud));
    cellN->nd = next;

    cellN->suiv = prevC->nd->voisins;
    prevC->nd->voisins = cellN;

    prevC->suiv = next->voisins;
    next->voisins = prevC;

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
        cndPrev = (CellNoeud*) calloc(1, sizeof(CellNoeud*));
        cndPrev->nd = noeudTete;
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
            // resolu pour l'instant
            cndPrev = ajouterVoisin(cndPrev, noeudTmp);

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


// int nbLiaisons(Reseau *R){
//     //compte le nombre de liaisons qui existent dans le Reseau R
//     int cnt = 0;
//     CellNoeud *tmp = R->noeuds;
//     //on doit utiliser une methode qui ignore les noeuds deja verifies, pour eviter de compter une liaison plusieurs fois
//     CellNoeud *vus = NULL;
//     while (tmp)
//     {
        
//     }
// }
// 
// void ecrireReseau(Reseau *R, FILE *f){
//     fprintf(f, "NbNoeuds: %d\n", R->nbNoeuds);
//     fprintf(f, "NbLiaisons: %d\n", nbLiaisons(R));
//     fprintf(f, "NbCommodites: %d\n", nbCommodites(R));
//     fprintf(f, "Gamma: %d\n", R->gamma);
//     fprintf(f,"\n");

//     int cpt = 0;// pour securiser le processus
//     CellNoeud* cnd = R->noeuds;
//     Noeud* nd = NULL;
//     while(cnd){
//         assert(cpt<R->nbNoeuds);
//         nd = cnd->nd;
//         fprintf(f, "v %d %.6lf %.6lf\n", nd->num, nd->x, nd->y);
//         cnd = cnd->suiv;
//         cpt++;
//     }
//     fprintf(f,"\n");

//     cnd = R->noeuds;
//     Noeud* nd2 = NULL;
//     CellNoeud* cndVoisin = ;
//     while(cndVoisin){

//     }


// }

void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}

