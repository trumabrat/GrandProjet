#include "Reseau.h"
#include "chaine.h"

int main()
{
    FILE* f = NULL;
    f = fopen("00014_burma.cha", "r");
    Chaines *c = lectureChaines(f);
    fclose(f);
    // afficheChainesSVG(c, "chaine");
    
    Reseau *R = reconstitueReseauListe(c);

    CellNoeud *tmp = R->noeuds;
    FILE* f2 = NULL;
    f2 = fopen("res.txt", "w");
    ecrireReseau(R, f2);
    fclose(f2);
    afficheReseauSVG(R, "reso");
    libererChaines(c);
    return 0;
}
