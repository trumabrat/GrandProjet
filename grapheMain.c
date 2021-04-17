#include "Graphe.h"
#include "ArbreQuat.h"
#include <stdio.h>

int main()
{
    FILE* f = fopen("00014_burma.cha", "r");
    Chaines* c = lectureChaines(f);
    Reseau* r = reconstitueReseauArbre(c);
    Graphe* g = creerGraphe(r);
    fclose(f);

    for (int i = 0; i < g->nbsom; i++)
    {
        for (int j = 0; j < g->nbsom; j++)
        {
            printf("%d\n", plus_petit_chemin(g, i, j));
        }
        
    }
    
    
    liberer_chaines(c);
    liberation_reseau(r);
    liberation_graph(g);
    return 0;
}
