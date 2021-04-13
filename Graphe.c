#include "Graphe.h"
#include <stdlib.h>
#include <stdio.h>

Graphe *creerGraphe(Reseau *R){
    //creation d'un graphe a partir d'un reseau

    //initiation du graphe
    Graphe *G = calloc(1, sizeof(Graphe));
    G->nbsom = R->nbNoeuds;
    G->gamma = R->gamma;
    G->T_som = calloc(G->nbsom, sizeof(Sommet*));
    G->T_commod = calloc(nbCommodites(R), sizeof(Commod));

    CellNoeud *tmp_CellNoeud = R->noeuds;
    while(tmp_CellNoeud){
        // Le num du sommet correspond a la position num-1 dans le tableau des sommets (tab est de 0 à nbNoeuds exclu)
        G->T_som[tmp_CellNoeud->nd->num - 1]->L_voisin;
        G->T_som[tmp_CellNoeud->nd->num - 1]->num = tmp_CellNoeud->nd->num;
        G->T_som[tmp_CellNoeud->nd->num-1]->x = tmp_CellNoeud->nd->x;
        G->T_som[tmp_CellNoeud->nd->num-1]->y = tmp_CellNoeud->nd->y;

        //On cree les arretes
        
        CellNoeud *tmp_voisins = tmp_CellNoeud->nd->voisins;
        while(tmp_voisins){
            //On ajoute une arrete que dans le cas ou le num du voisin est plus grand que celui de notre cell courante
            //dans le cas contraire, l'arrete est deja ajoutée
            if(tmp_CellNoeud->nd->num < tmp_voisins->nd->num){
                //Allocation d'une nouvelle Cellule_arete et Arete
                Cellule_arete *tmpCellArr = calloc(1, sizeof(Cellule_arete));
                tmpCellArr->suiv = G->T_som[tmp_CellNoeud->nd->num-1]->L_voisin;
                tmpCellArr->a = calloc(1, sizeof(Arete));

                //attributions des valeures
                tmpCellArr->a->u = tmp_CellNoeud->nd->num;
                tmpCellArr->a->v = tmp_voisins->nd->num;

                //ajout en tete de L_voisins de la nouvelle Cellule_arete
                G->T_som[tmp_CellNoeud->nd->num - 1]->L_voisin = tmpCellArr;

                //On ajoute la meme arrete dans une deuxieme Cell_arrete qu'on ratache au sommet voisin
                Cellule_arete *tmpCellArr2 = calloc(1, sizeof(Cellule_arete));
                tmpCellArr2->suiv = G->T_som[tmp_voisins->nd->num - 1]->L_voisin;
                tmpCellArr2->a = tmpCellArr->a;
                G->T_som[tmp_voisins->nd->num - 1]->L_voisin = tmpCellArr2;

                tmp_voisins = tmp_voisins->suiv;
            }
        }

        tmp_CellNoeud = tmp_CellNoeud->suiv;
    }

    int commod_cmp = 0;

    CellCommodite *tmp_CellCommodite = R->commodites;

    //On s'occupe du tableau de commodites
    while (tmp_CellCommodite)
    {
        G->T_commod[commod_cmp].e1 = tmp_CellCommodite->extrA->num;
        G->T_commod[commod_cmp].e2 = tmp_CellCommodite->extrB->num;
        commod_cmp++;
        tmp_CellCommodite = tmp_CellCommodite->suiv;
    }
}