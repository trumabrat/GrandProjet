#include "chaine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    /* 
        lecture et creation d'une instance de Chaines
        on peut decommenter pour choisir l'instance qu'on va verifier
    */

    // FILE* f = fopen("00014_burma.cha", "r");
    // FILE* f = fopen("05000_USA-road-d-NY.cha", "r");
    FILE* f = fopen("07397_pla.cha", "r");
    // FILE* f = fopen("test.cha", "r");
    
    // FILE *f2 = fopen("00014_burma_res.txt", "w");
    // FILE* f2 = fopen("05000_USA-road-d-NY_res.txt", "w");
    FILE* f2 = fopen("07397_pla.cha_res", "w");
    // FILE* f2 = fopen("test_res.cha", "w");
    Chaines *c = lectureChaines(f);
    ecrireChaines(c, f2);

    // affichage de cette Chaines
    afficheChainesSVG(c, "Chaines");
    printf("LongueurTotal = %lf, nombre de points = %d\n", longueurTotale(c), comptePointsTotal(c));

    // fermeture des fichiers et liberation
    liberer_chaines(c);
    fclose(f);
    fclose(f2);
    return 0;
}
