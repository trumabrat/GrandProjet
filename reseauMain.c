#include "Reseau.h"
#include "chaine.h"

int main()
{
    // lecture et creation d'une instance de Chaines et de Reseau
    FILE* f = NULL;
    f = fopen("00014_burma.cha", "r");
    Chaines *c = lectureChaines(f);
    fclose(f);
    Reseau *R = reconstitueReseauListe(c);
    
    // affichage et l'enregistrement
    afficheChainesSVG(c, "chaineReseau");
    FILE* f2 = NULL;
    f2 = fopen("res.txt", "w");
    ecrireReseau(R, f2);
    fclose(f2);
    afficheReseauSVG(R, "reso");
    
    return 0;
}
