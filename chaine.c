#include "chaine.h"
#include "SVGwriter.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Chaines* lectureChaines(FILE* f){
    int nbChaine, gamma;
    int length = 100;
    char buffer[length];

    // recuperer le nombre de chaines
    fgets(buffer, length, f);
    sscanf(buffer, " %*s %d", &nbChaine);
    if(nbChaine == 0){
        printf("Erreur : nbChaine = 0 dans le fichier.");
        return NULL;
    }

    // recuperer la valeur de gamma
    fgets(buffer, length, f);
    sscanf(buffer, " %*s %d", &gamma);
    
    //creer une instance de Chaines
    Chaines* res = (Chaines*) calloc(1, sizeof(Chaines));
    res->nbChaines = nbChaine;
    res->gamma = gamma;
    
    // creer les CellChaine
    res->chaines = creerCellChaineRec(nbChaine, f);

    return res;
}

// liberer Chaines d'une maniere recursive
void libererChaines(Chaines* chaines){
    libererCellChaineRec(chaines->chaines);
    free(chaines);
}

// creer CellPoint d'une maniere recursive
CellPoint* creerCellPointRec(int nb, FILE* f){
    if(nb == 0) return NULL;
    CellPoint* unPoint = (CellPoint*) malloc(sizeof(CellPoint));
    fscanf(f, " %lf %lf", &(unPoint->x), &(unPoint->y));
    unPoint->suiv = creerCellPointRec(nb-1, f);
    return unPoint;
}

// liberer CellPoint d'une maniere recursive
void libererCellPointRec(CellPoint* p){
    if(!p) return;
    libererCellPointRec(p->suiv);
    free(p);
}

// creer CellChaine d'une maniere recursive
CellChaine* creerCellChaineRec(int nb, FILE* f){
    if(nb == 0) return NULL;
    CellChaine* res = (CellChaine*) calloc(1, sizeof(CellChaine));
    int nbPoints;
    if(fscanf(f, " %d %d", &(res->numero), &nbPoints) == 2){
        res->points = creerCellPointRec(nbPoints, f);
        res->suiv = creerCellChaineRec(nb-1, f);
    }
    return res;
}

// liberer CellChaine d'une maniere recursive
void libererCellChaineRec(CellChaine* ch){
    if(!ch) return;
    libererCellChaineRec(ch->suiv);
    libererCellPointRec(ch->points);
    free(ch);
}

//Cette fonction va ecrire une instance de "Listes de Chaines" sous le format precisé en exercice 1
void ecrireChaines(Chaines *C,FILE *f){
    if (C==NULL || f==NULL)
        return;
    fprintf(f, "NbChain: %d\n", C->nbChaines);
    fprintf(f, "Gamma: %d\n", C->gamma);
    CellChaine *tmp = C->chaines;
    
    while (tmp)
    {
        CellPoint *tmp_points = tmp->points;
        int counter = 0;
        //On fait un premier tour pour obtenir le nombre des points de la chaine
        while(tmp_points){
            counter++;
            tmp_points = tmp_points->suiv;
        }
        //On ecrit le numero de la chaine, et le nombre des points
        fprintf(f,"%d %d ", tmp->numero, counter);

        //Ici, on va ecrire les coordonnées des points
        tmp_points = tmp->points;
        while(tmp_points){
            fprintf(f,"%.2lf %.2lf ", tmp_points->x, tmp_points->y);
            tmp_points = tmp_points->suiv;
        }

        //On saute une ligne quand on finit avec tous les points de la chaine
        fprintf(f, "\n");
        tmp = tmp->suiv;
    }
}

void afficheChainesSVG(Chaines *C, char* nomInstance){
    int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}

// renvoie la distance entre 2 points si non vide
double distancePoints(CellPoint* p1, CellPoint* p2){
    if(!p1 || !p2) return 0.;
    return sqrt(pow(p1->x - p2->x,2) + pow(p1->x - p2->x, 2));
}

// renvoie la longueur d'une chaine
double longueurChaine(CellChaine* c){
    double res = 0.;
    if(c){
        CellPoint* cur = c->points;
        CellPoint* next = c->points->suiv;
        while(next){
            res += distancePoints(cur, next);
            cur = next;
            next = next->suiv;
        }
    }
    return res;
}

// renvoie la longueur de toutes les chaines
double longueurTotale(Chaines *C){
    double res = 0.;
    if(C){
        CellChaine* ch = C->chaines;
        while(ch){
            res += longueurChaine(ch);
            ch = ch->suiv;
        }
    }
    return res;
}

int comptePointsTotal(Chaines *C){
    int res = 0;
    if(C){
        CellChaine* curCellChaine = C->chaines;
        CellPoint* curPoint = NULL;
        while (curCellChaine)
        {
            curPoint = curCellChaine->points;
            while(curPoint){
                res++;
                curPoint = curPoint->suiv;
            }
            curCellChaine = curCellChaine->suiv;
        }
    }
    return res;
}