#include "ArbreQuat.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void chaineCoordMinMax(Chaines *C, double *xmin, double *ymin, double *xmax, double *ymax){
    /*On cherche les 4 coordonées les plus petites qui se trouvent dans nos chaines C,
    xmin et ymin (meme pour xmax, ymax) vont pas etre le meme point, c seulement les 
    valeurs minimales (resp. maximales) de toutes les coordonées des points*/

    if (C==NULL || C->chaines==NULL){
        printf("Pas de chaines");
        return;
    }

    double tmp_xmin = INFINITY;
    double tmp_ymin = INFINITY;
    double tmp_xmax = -INFINITY;
    double tmp_ymax = -INFINITY;

    CellChaine *tmp_chaine = C->chaines;

    /*On parcourt tous les points de toutes les chaines*/
    while (tmp_chaine){
        CellPoint *tmp_points = tmp_chaine->points;
        while(tmp_points){
            /*Verification si on a trouvé un nouveau xmin, ymin, xmax ou ymax */
            if (tmp_points->x < tmp_xmin){
                tmp_xmin = tmp_points->x;
            }
            if (tmp_points->y < tmp_ymin){
                tmp_ymin = tmp_points->y;
            }
            if (tmp_points->x > tmp_xmax){
                tmp_xmax = tmp_points->x;
            }
            if (tmp_points->y > tmp_ymax){
                tmp_ymax = tmp_points->y;
            }

            tmp_points = tmp_points->suiv;
        }
        tmp_chaine = tmp_chaine->suiv;
    }

    *xmin = tmp_xmin;
    *xmax = tmp_xmax;
    *ymin = tmp_ymin;
    *ymax = tmp_ymax;
}

ArbreQuat *creerArbreQuat(double xc, double yc, double coteX, double coteY){
    /*Création simple d'un ArbreQuat*/
    ArbreQuat *new = malloc(sizeof(ArbreQuat));
    new->xc = xc;
    new->yc = yc;
    new->coteX = coteX;
    new->coteY = coteY;

    new->noeud = NULL;
    new->ne = NULL;
    new->no = NULL;
    new->se = NULL;
    new->so = NULL;

    return new;
}