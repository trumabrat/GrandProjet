#include "ArbreQuat.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define DOUBLE_PRECISION 0.00001

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

void insererNoeudArbre(Noeud *n, ArbreQuat **a, ArbreQuat *parent){
    if (*a == NULL){
        // Si il n'existe pas de abre a crée, on crée un nouveau et on insére dans l'un des fils du parent
        /*L'hypoyhèse est que si *a==NULL, alors ca veut dire l'enfant du parent ou doit aller le noeud est vide
        Si ce n'est pas le cas, cette fonction va écraser ce qui se trouver dans cet enfant du parent*/

        //Longueur et largeur de l'arbre a
        double newCoteX = parent->coteX / 2.0;
        double newCoteY = parent->coteY / 2.0;

        //cas sud-ouest
        if (n->x < parent->xc && n->y < parent->yc)
        {
            *a = creerArbreQuat(parent->xc - newCoteX / 2.0, parent->yc - newCoteY / 2.0, newCoteX, newCoteY);
            (*a)->noeud = n;
            parent->so = *a;
        }

        //cas sud-est
        if (n->x >= parent->xc && n->y < parent->yc){
            *a = creerArbreQuat(parent->xc + newCoteX / 2.0, parent->yc - newCoteY / 2.0, newCoteX, newCoteY);
            (*a)->noeud = n;
            parent->se = *a;
        }

        //cas nord-ouest
        if (n->x < parent->xc && n->y >= parent->yc){
            *a = creerArbreQuat(parent->xc - newCoteX / 2.0, parent->yc + newCoteY / 2.0, newCoteX, newCoteY);
            (*a)->noeud = n;
            parent->no = *a;
        }

        //cas nord-est
        if(n->x >= parent->xc && n->y >= parent->yc){
            *a = creerArbreQuat(parent->xc + newCoteX / 2.0, parent->yc + newCoteY / 2.0, newCoteX, newCoteY);
            (*a)->noeud = n;
            parent->ne = *a;
        }

        return;
    }

    else{
        if ((*a)->noeud != NULL){
            /*Ici on considère le cas ou l'arbre a est une feuille (noeud présent).
            L'arbre cesse alors d'etre une feuille mais devient une racine, et ces dans ses feuilles
            qu'on va vouloir insérer les valeurs.Si les points sont très prêts les uns des autres, on
            peut également imaginer qu'on doit transformer la racine des enfants de l'arbre a aussi.*/

            //a devient le parent, on transfere son noeud vers l'un des fils de a.
            insererNoeudArbre((*a)->noeud, NULL, *a);
            (*a)->noeud = NULL;

            insererNoeudArbre(n, a, parent);
            //Maintenant, la feuille est devenu une cellule interne, donc la clause d'après va décider ou mettre le noeud.
            //Si le noeud doit aller dans la feuille déjà occupé par le noeud qui existait dans *(a)->noeud, le procès se repète.
        }

        else{
            /*si on se trouve dans une cellule interne, on cherche ou placer le noeud n en comparant les coordonées du noeud
            par rapport au centre. On peut alors soit arriver rencontrer l'espace libre pour insérer notre noeud, soit rencontrer
            une feuille, ce qui va être géré dans le bloc d'avant.*/

            //cas sud-ouest
            if (n->x < (*a)->xc && n->y < (*a)->yc)
            {
                insererNoeudArbre(n, &((*a)->so), *a);
            }

            //cas sud-est
            if (n->x >= (*a)->xc && n->y < (*a)->yc){
               insererNoeudArbre(n, &((*a)->se), *a);
            }

            //cas nord-ouest
            if (n->x < (*a)->xc && n->y >= (*a)->yc){
                insererNoeudArbre(n, &((*a)->no), *a);
            }

            //cas nord-est
            if(n->x >= (*a)->xc && n->y >= (*a)->yc){
                insererNoeudArbre(n, &((*a)->ne), *a);
            }
        }
    }
}

Noeud *rechercheCreeNoeudArbre(Reseau *R, ArbreQuat **a, ArbreQuat *parent, double x, double y){
    if ((*a)==NULL){
        //On doit insérér le noeud x,y dans l'arbre ainsi que dans reseau

        //insertion dans le reseau
        R->nbNoeuds++;
        CellNoeud *new = malloc(sizeof(CellNoeud));
        new->nd = creerNoeud(R->nbNoeuds, x, y);
        new->suiv = R->noeuds;
        R->noeuds = new;

        //insertion dans l'arbre
        insererNoeudArbre(new->nd, a, parent);

        return new->nd;
    }

    else{
        if ((*a)->noeud != NULL){
            if (fabs((*a)->noeud->x - x) < DOUBLE_PRECISION  && fabs((*a)->noeud->y - y) < DOUBLE_PRECISION){
                //Le noeud existe dans l'arbre et donc dans le réseau, on retourne le noeud
                return (*a)->noeud;
            }
            else{
                //Le noeud n'existe pas dans l'arbre car on est arrivé a une feuille et le if n'est pas vérifié.
                //On ajoute au réseau
                R->nbNoeuds++;
                CellNoeud *new = malloc(sizeof(CellNoeud));
                new->nd = creerNoeud(R->nbNoeuds, x, y);
                new->suiv = R->noeuds;
                R->noeuds = new;

                //On ajoute dans l'arbre
                insererNoeudArbre(new->nd, a, parent);

                return new->nd;
            }
        }
        else{
            //On continue de chercher jusqu'a ce qu'on arrive a une feuille ou place libre
            //On doit déterminer dans lequel des enfants on doit chercher

            //cas sud-ouest
            if (x < (*a)->xc && y < (*a)->yc)
            {
                return rechercheCreeNoeudArbre(R, &((*a)->so), *a, x, y);
            }

            //cas sud-est
            if (x >= (*a)->xc && y < (*a)->yc){
               return rechercheCreeNoeudArbre(R, &((*a)->se), *a, x, y);
            }

            //cas nord-ouest
            if (x < (*a)->xc && y >= (*a)->yc){
                return rechercheCreeNoeudArbre(R, &((*a)->no), *a, x, y);
            }

            //cas nord-est
            if(x >= (*a)->xc && y >= (*a)->yc){
                return rechercheCreeNoeudArbre(R, &((*a)->ne), *a, x, y);
            }
        }
    }

    //Pour que le compilateur ne fait pas de pb, j'amais verifié
    return NULL;
}






