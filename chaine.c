#include "chaine.h"
#include "SVGwriter.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

Chaines* lectureChaines(FILE* f){
    int nbChaine, gamma;
    int numero, nbPoints, nbPointsCrees;
    CellPoint* unPoint = NULL;
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
    
    // creer les CellChaines
    CellChaine* cur = NULL;
    while(fgets(buffer, length, f)){
        if(sscanf(buffer, " %d %d", &numero, &nbPoints) != 2) continue;
        cur = (CellChaine*) calloc(1, sizeof(CellChaine));
        cur->numero = numero;
        for(nbPointsCrees = 0; nbPointsCrees < nbPoints; nbPointsCrees++){
            // printf("%s\n", buffer);
            unPoint = (CellPoint*) calloc(1, sizeof(CellPoint));
            sscanf(buffer, " %lf %lf", &(unPoint->x), &(unPoint->y));
            unPoint->suiv = cur->points;
            cur->points= unPoint;
        }
        cur->suiv = res->chaines;
        res->chaines = cur;
    }

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

// void afficheChainesSVG(Chaines *C, char* nomInstance){
//     int i;
//     double maxx=0,maxy=0,minx=1e6,miny=1e6;
//     CellChaine *ccour;
//     CellPoint *pcour;
//     double precx,precy;
//     SVGwriter svg;
//     ccour=C->chaines;
//     while (ccour!=NULL){
//         pcour=ccour->points;
//         while (pcour!=NULL){
//             if (maxx<pcour->x) maxx=pcour->x;
//             if (maxy<pcour->y) maxy=pcour->y;
//             if (minx>pcour->x) minx=pcour->x;
//             if (miny>pcour->y) miny=pcour->y;  
//             pcour=pcour->suiv;
//         }
//     ccour=ccour->suiv;
//     }
//     SVGinit(&svg,nomInstance,500,500);
//     ccour=C->chaines;
//     while (ccour!=NULL){
//         pcour=ccour->points;
//         SVGlineRandColor(&svg);
//         SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
//         precx=pcour->x;
//         precy=pcour->y;  
//         pcour=pcour->suiv;
//         while (pcour!=NULL){
//             SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
//             SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
//             precx=pcour->x;
//             precy=pcour->y;    
//             pcour=pcour->suiv;
//         }
//         ccour=ccour->suiv;
//     }
//     SVGfinalize(&svg);
// }