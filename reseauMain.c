#include "Reseau.h"
#include "chaine.h"

int main()
{
    FILE* f = NULL;
    f = fopen("00014_burma.cha", "r");
    Chaines *c = lectureChaines(f);
    fclose(f);
    // afficheChainesSVG(c, "chaine");
    
    reconstitueReseauListe(c);

    // FILE *f2 = fopen("ecriture_chaine.cha", "w");
    // ecrireChaines(c, f2);
    // fclose(f2);
    libererChaines(c);
    return 0;
}
