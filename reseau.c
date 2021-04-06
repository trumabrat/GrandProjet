#include "Reseau.h"
#include "SVGwriter.h"
#include <math.h>
#include <assert.h>
#define DOUBLE_PRECISION 0.00001

// recherche d'un Noeud dans un reseau a partir de ses coordonnees
// si on ne le trouve pas, on le cree
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    int i;
    CellNoeud* cellnoeud = R->noeuds;
    Noeud* noeud = NULL;

    // recherche dans la liste
    for (i = 0; i < R->nbNoeuds && cellnoeud; i++, cellnoeud = cellnoeud->suiv)
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

// creer une CellNoeud a partir d'un Noeud et la CellNoeud suivante
CellNoeud* creerCellNoeud(Noeud* n, CellNoeud* suiv){
    CellNoeud* res = (CellNoeud*) calloc(1, sizeof(CellNoeud));
    res->nd = n;
    res->suiv = suiv;
    return res;
}


// mise a jour les listes des voisins des Noeud prev et next
// retourne un pointeur vers le Noeud next
Noeud* ajouterVoisin(Noeud* prev, Noeud* next){
    // verification
    if(!next) return NULL;

    // si les deux sont deja voisins, on renvoie Noeud next directement
    CellNoeud* tmp = prev->voisins;
    while(tmp){
        if(tmp->nd == next){
            return next;
        }
        tmp = tmp->suiv;
    }

    // Sinon, on cree CellNoeud correspondants et tisse les liens
    CellNoeud* cellN = creerCellNoeud(next, prev->voisins);
    prev->voisins = cellN;
    next->voisins = creerCellNoeud(prev, next->voisins);

    return next;
}

// creer une CellCommodite a partir de son deux Noeud extremite, et CellCommodite suivante
CellCommodite* creerCellCommodite(Noeud* extrA, Noeud* extrB, CellCommodite* suiv){
    CellCommodite* res = (CellCommodite*) calloc(1, sizeof(CellCommodite));
    res->extrA = extrA;
    res->extrB = extrB;
    res->suiv = suiv;
    return res;
}

// On reconstruire un Reseau a partir d'une Chaines
Reseau* reconstitueReseauListe(Chaines *C){
    int i;
    Reseau* reso = (Reseau*) calloc(1, sizeof(Reseau));
    reso->gamma = C->gamma;

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
        noeudTete = rechercheCreeNoeudListe(reso, pointTmp->x, pointTmp->y);
        noeudPrev = noeudTete;
        pointPrev = pointTmp;
        pointTmp = pointTmp->suiv;

        // Pour chaque point p de la cha^ıne:
        while(pointTmp){
            // Si p !∈ V (on teste si le point n’a pas d´ej`a ´et´e rencontr´e auparavant)
                // On ajoute dans V un nœud correspond au point p.
            noeudTmp = rechercheCreeNoeudListe(reso, pointTmp->x, pointTmp->y);
            
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

//compte le nombre de liaisons qui existent dans le Reseau R
int nbLiaisons(Reseau *R){ 
    int cnt = 0;
    CellNoeud *tmp = R->noeuds;
    while (tmp)
    {
        CellNoeud *voisins = tmp->nd->voisins;
        while(voisins){
            cnt++;
            voisins = voisins->suiv;
        }
        tmp = tmp->suiv;
    }

    //on va diviser le compteur par 2, car on a compté chaque liaison 2 fois
    return (cnt/2);
}

//compte le nombre de commoditées dans le Reseau R
int nbCommodites(Reseau *R){ 
    int cmp = 0;
    CellCommodite *tmp = R->commodites;
    while(tmp){
        cmp++;
        tmp = tmp->suiv;
    }

    return cmp;
}

// sauvegarder l'information d'un Reseau dans un fichier
void ecrireReseau(Reseau *R, FILE *f){
    // sauvegarde de l'information fondamentale
    fprintf(f, "NbNoeuds: %d\n", R->nbNoeuds);
    fprintf(f, "NbLiaisons: %d\n", nbLiaisons(R));
    fprintf(f, "NbCommodites: %d\n", nbCommodites(R));
    fprintf(f, "Gamma: %d\n", R->gamma);
    fprintf(f,"\n");

    int cpt = 0;// pour securiser le processus
    CellNoeud* cnd = R->noeuds;
    Noeud* nd = NULL;

    // l'enregistrement de l'information des Noeud
    while(cnd){
        assert(cpt<R->nbNoeuds);
        nd = cnd->nd;
        fprintf(f, "v %d %.6lf %.6lf\n", nd->num, nd->x, nd->y);
        cnd = cnd->suiv;
        cpt++;
    }
    fprintf(f,"\n");

    // l'enregistrement de l'information des liasons
    CellNoeud* cndVoisin = NULL;
    //Pour chaque noeud du reseau
    for (cnd = R->noeuds, cpt = 0; cnd ; cnd = cnd->suiv, cpt++)
    {
        assert(cpt < R->nbNoeuds);// securisation
        cndVoisin = cnd->nd->voisins;

        // Pour chaque voisin
        while(cndVoisin){
            if(cndVoisin->nd->num < cnd->nd->num){ // pour une liaison n'apparaisse deux fois
                fprintf(f, "l %d %d\n", cndVoisin->nd->num, cnd->nd->num);
            }
            cndVoisin = cndVoisin->suiv;
        }
    }
    fprintf(f, "\n");

    // l'enregistrement de l'information des commodite
    CellCommodite* cell_com = R->commodites;
    while (cell_com)
    {
        fprintf(f, "k %d %d\n", cell_com->extrA->num, cell_com->extrB->num);
        cell_com = cell_com->suiv;
    }
    fprintf(f,"\n");
}

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

void liberation_chaine_CellNoeud(CellNoeud *Cells){
    CellNoeud* tmp = NULL;
    while(Cells){
        tmp = Cells;
        Cells = Cells->suiv;
        free(tmp);
    }
}

void liberation_cell_noeud(CellNoeud *noeuds){
    //liberations des noeuds dans CellNoeuds
    //on ne s'occupe pas des voisins puisqu'il se trouvent dans les suivants de CellNoeuds aussi
    if(noeuds->suiv){
        liberation_cell_noeud(noeuds->suiv);
    }
    liberation_chaine_CellNoeud(noeuds->nd->voisins);
    free(noeuds->nd);
    free(noeuds);
}

void liberation_cell_commodite(CellCommodite *cellC){
    //liberation des commodites, les extremites sont liberes par liberations cell noeuds
    if (cellC->suiv){
        liberation_cell_commodite(cellC->suiv);
    }
    free(cellC);
}

void liberation_reseau(Reseau *R){
    //liberation du reseau
    liberation_cell_commodite(R->commodites);
    liberation_cell_noeud(R->noeuds);
    free(R);
}