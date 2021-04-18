#include "Graphe.h"
#include "ArbreQuat.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    FILE* f = fopen("test.cha", "r");
    Chaines* c = lectureChaines(f);
    Reseau* r = reconstitueReseauArbre(c);
    Graphe* g = creerGraphe(r);
    fclose(f);
    printf("nb noeuds: %d\n", r->nbNoeuds);
    for (int i = 0; i < g->nbsom; i++)
    {
        for (int j = 0; j < g->nbsom; j++)
        {
            // printf("(%d, %d) : %d\t", i, j, plus_petit_chemin(g, i, j));
            // assert(plus_petit_chemin(g,i,j) == plus_petit_chemin(g,j,i));
        }
        putchar('\n');
    }
    afficheChainesSVG(c, "testMyinstance");
    ListeEntier parcourt = chaine_arborescence(g, 0, 5);
    afficher_liste_entier(&parcourt);
    desalloue(&parcourt);
    
    liberer_chaines(c);
    liberation_reseau(r);
    liberation_graph(g);
    return 0;
}
