#include "chaine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE* f = NULL;
    f = fopen("00014_burma.cha", "r");
    Chaines *c = lectureChaines(f);
    FILE *f2 = fopen("ecriture_chaine.cha", "w");
    ecrireChaines(c, f2);
    // afficheChainesSVG(c, "chaine");
    fclose(f);
    fclose(f2);
    return 0;
}
