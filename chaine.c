#include "chaine.h"
#include "SVGwriter.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


// pour creer une instance Chaines a partir d'un fichier
Chaines* lectureChaines(FILE *f){

    Chaines *res = (Chaines *)calloc(1,sizeof(Chaines));
    int nbChaine, gamma;
    int num, nbPoints;
    double x, y;

    // recuperer le nombre de chaines
    fscanf(f," %*s %d" , &nbChaine);

    // recuperer la valeur de gamma
    fscanf(f," %*s %d" , &gamma);

    res->nbChaines = nbChaine;
    res->gamma = gamma;
    CellChaine *liste_chaine = NULL;
    CellChaine *chaine_cur = NULL;
    CellPoint *liste_point = NULL;
    
    // pour chaque chaine
    for(int j =  0 ;  j < nbChaine ; j++){
        chaine_cur = (CellChaine *)calloc(1, sizeof(CellChaine));
        // on prend le nombre de points
        fscanf(f," %d %d", &num, &nbPoints);
        chaine_cur->numero = num;
        liste_point = NULL;

        // pour chaque point d'une chaine
        for(int i = 0 ; i < nbPoints; i++){
            CellPoint *point = (CellPoint*)malloc(sizeof(CellPoint));
            fscanf(f,"%lf %lf ", &x, &y);
            point->x = x;
            point->y = y;
            point->suiv = liste_point;
            liste_point = point;
        }

        // on passe a suivant
        chaine_cur->points = liste_point;
        chaine_cur->suiv = liste_chaine;
        liste_chaine = chaine_cur;
    }
    
    res->chaines = liste_chaine;
    return res;
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

// compter le nombre de points apparus dans Chaines, meme s'ils sont presents plusieur fois
int comptePointsTotal(Chaines *C){
    int res = 0;
    if(C){
        CellChaine* curCellChaine = C->chaines;
        CellPoint* curPoint = NULL;

        // pour chaque CellChaine
        while (curCellChaine)
        {
            curPoint = curCellChaine->points;

            // pour chaque Point
            while(curPoint){
                res++;
                curPoint = curPoint->suiv;
            }
            curCellChaine = curCellChaine->suiv;
        }
    }
    return res;
}

void liberer_cell_point(CellPoint *cellP){
    //liberation du cellPoint
    if (cellP->suiv){
        liberer_cell_point(cellP->suiv);
    }
    free(cellP);
}

void liberer_cell_chaine(CellChaine *cellC){
    //liberation du CellChaine
    if (cellC->suiv){
        liberer_cell_chaine(cellC->suiv);
    }
    liberer_cell_point(cellC->points);
    free(cellC);
}

void liberer_chaines(Chaines *C){
    liberer_cell_chaine(C->chaines);
    free(C);
}