#include "Graphe.h"
#include "ArbreQuat.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    // creation du graphe
    // voici les graphes a choisir

    FILE* f = fopen("00014_burma.cha", "r");
    // FILE* f = fopen("05000_USA-road-d-NY.cha", "r");
    // FILE* f = fopen("07397_pla.cha", "r");
    // FILE* f = fopen("test.cha", "r");
    Chaines* c = lectureChaines(f);
    Reseau* r = reconstitueReseauArbre(c);
    Graphe* g = creerGraphe(r);
    fclose(f);
    
    if(reorganiserReseau(r)) {
        printf("ok!\n");
    }
    // Q7.5
    // 

    // liberation de memoire
    liberer_chaines(c);
    liberation_reseau(r);
    liberation_graph(g);
    return 0;
}
