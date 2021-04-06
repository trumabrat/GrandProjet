#include "comparaisons.h"
#include <time.h>

int main()
{
    // lecture et creation d'une instance de Chaines et de Reseau
    FILE* f = NULL;
    f = fopen("00014_burma.cha", "r");
    Chaines *c = lectureChaines(f);
    fclose(f);

    // construction du reseau, hachage et arbre
    // avec calcul du temps, et son ecriture dans un fichier
    clock_t start, end;
    FILE* f2 = NULL;
    start = clock();
    Reseau *L = reconstitueReseauListe(c);
    end = clock();
    
    Reseau *H = reconstitueReseauHachage(c, 5);
    Reseau* A = reconstitueReseauArbre(c);

    // liberation de memoire
    liberer_chaines(c);
    liberation_reseau(L);
    liberation_reseau(H);
    liberation_reseau(A);
    return 0;
}
