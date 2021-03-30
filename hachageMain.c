#include "Hachage.h"


int main()
{
    float k;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            k = fonctionCle(i, j);
            printf("x = %d, y = %d, k = %.2f\n", i, j, k);
        }
    }
    TableHachage* tbh = creerTableHachage(10);
    // FILE* f = NULL;
    // f = fopen("00014_burma.cha", "r");
    // Chaines *c = lectureChaines(f);
    // fclose(f);
    // Reseau *R = reconstitueReseauListe(c);
    // libererChaines(c);
    return 0;
}
