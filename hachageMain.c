#include "Hachage.h"
#include "chaine.h"


int main()
{
    // Q4.2
    float k;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            k = fonctionCle(i, j);
            printf("x = %d, y = %d, k = %.2f\n", i, j, k);
        }
    }

    // lecture et creation d'une instance de Chaines et de Reseau
    FILE* f = NULL;
    f = fopen("00014_burma.cha", "r");
    Chaines *c = lectureChaines(f);
    fclose(f);
    Reseau *R = reconstitueReseauHachage(c, 5);
    FILE* f2 = NULL;

    // l'enregistrement dans un fichier
    f2 = fopen("resHachage.txt", "w");
    ecrireReseau(R, f2);
    fclose(f2);

    // affichage
    afficheReseauSVG(R, "resoHachage");
    
    return 0;
}
