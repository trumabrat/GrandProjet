#include "Graphe.h"
#include "Struct_File.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

Graphe *creerGraphe(Reseau *R){
    //creation d'un graphe a partir d'un reseau

    //initiation du graphe
    Graphe *G = calloc(1, sizeof(Graphe));
    G->nbsom = R->nbNoeuds;
    G->gamma = R->gamma;
    G->nbcommod = nbCommodites(R);
    G->T_som = calloc(G->nbsom, sizeof(Sommet*));
    G->T_commod = calloc(G->nbcommod, sizeof(Commod));

    CellNoeud *tmp_CellNoeud = R->noeuds;
    while(tmp_CellNoeud){
        // Le num du sommet correspond a la position num-1 dans le tableau des sommets (tab est de 0 à nbNoeuds exclu)
        G->T_som[tmp_CellNoeud->nd->num-1] = calloc(1, sizeof(Sommet));
        // G->T_som[tmp_CellNoeud->nd->num - 1]->L_voisin   à finir;
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

                // tmp_voisins = tmp_voisins->suiv;
            }
            tmp_voisins = tmp_voisins->suiv; // passe au voisin suivant
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
    assert(commod_cmp == G->nbcommod);
    return G;
}

// fonction de liberation pour une liste d'aretes
// en particulier, pour la liste de voisins d'un sommet
void libere_liste_aretes(Cellule_arete* cell_a){
    // on parcourt cette liste chainee
    // si cette arete est visite pour la premiere fois, on met u a -1
    // pour la deuxieme fois on la libere (cela evitera la double free)
    // cependant, on libere toutes les cellules qu'on vues
    Cellule_arete* tmp = NULL;
    while(cell_a){
        if (cell_a->a->u == -1){
            free(cell_a->a);
        }else{
            cell_a->a->u = -1;
        }
        tmp = cell_a;
        cell_a = cell_a->suiv;
        free(tmp);
    }
}

// fonction de liberation pour un graphe
void liberation_graph(Graphe* g){
    // liberation pour les listes de voisins
    for (int i = 0; i < g->nbsom; i++)
    {
        libere_liste_aretes(g->T_som[i]->L_voisin);
        free(g->T_som[i]);
    }

    // liberation de graphe
    free(g->T_commod);
    free(g->T_som);
    free(g);
}

// on cheche le longeur du chemin le plus court entre les sommets u et v
int plus_petit_chemin(Graphe* g, int u, int v){
    // Dans chaque iteration, on prend le sommet a la tete de la file
    // et enfile les sommets adjacent mais non visite
    // on continue cette boucle jusqu'a ce qu'on touche le sommet v

    // securisation
    assert(g);
    assert(u < g->nbsom && v <g->nbsom);
    if(u == v) return 0;

    int sommet_en_cours, sommet_prochain, a_enfiler, cptDistance = 0;
    Cellule_arete* cell_arete;

    // on cree une table pour memoriser les sommet visite
    int visite[g->nbsom];
    for (int i = 0; i < g->nbsom; i++)
    {
        visite[i] = 0;
    }
    visite[u] = 1;

    // on cree une autre table pour stocker les distances entre u et les sommets
    int distance[g->nbsom];
    for (int i = 0; i < g->nbsom; i++)
    {
        distance[i] = 0;
    }
    
    // on cree un file pour les sommets a visiter
    S_file* file = calloc(1, sizeof(S_file));
    Init_file(file);
    enfile(file, u);

    // on fait un parcourt en largeur jusqu'a ce que la file est vide
    while(visite[v] != 1){
        // si on a pas visite le sommet v et la file est deja vide
        // c'est parce que u et v n'est pas connexe
        if(estFileVide(file)) return -1;

        // on prend la tete de la file et parcourt sa liste de voisins
        // et enfile les sommets prochains
        sommet_en_cours = defile(file);
        cell_arete = g->T_som[sommet_en_cours]->L_voisin;
        while(cell_arete){
            // on teste le numero de sommet a enfiler
            // a_enfiler = cell_arete->a->u == sommet_en_cours ? v : u;
            if(cell_arete->a->u == sommet_en_cours) 
                 a_enfiler = cell_arete->a->v;
            else a_enfiler = cell_arete->a->u;
            
            // si deja visite, on ne prend pas, sinon on le prend et note sa distance
            if(visite[a_enfiler] == 0){
                enfile(file, a_enfiler);
                if(distance[a_enfiler] == 0 || (distance[sommet_en_cours]+1 < distance[a_enfiler])){
                    distance[a_enfiler] = distance[sommet_en_cours]+1;
                }
            }
            cell_arete = cell_arete->suiv;
        }
        visite[sommet_en_cours] = 1;
    }
    liberer_file(file);

    return distance[v];
}