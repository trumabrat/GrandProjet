#include "chaine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* f = NULL;
    f = fopen("00014_burma.cha", "r");
    Chaines *c = lectureChaines(f);
    // FILE *f2 = fopen("ecriture_chaine.cha", "w");
    // ecrireChaines(c, f2);
    afficheChainesSVG(c, "chaine");
    printf("LongueurTotal = %lf, nombre de points = %d\n", longueurTotale(c), comptePointsTotal(c));
    libererChaines(c);
    fclose(f);
    // fclose(f2);
    return 0;
}
