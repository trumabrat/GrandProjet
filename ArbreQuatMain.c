#include "ArbreQuat.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE* f = NULL;
    f = fopen("00014_burma.cha", "r");
    Chaines *C = lectureChaines(f);

    // double xmin, ymin, xmax, ymax;
    // chaineCoordMinMax(C, &xmin, &ymin, &xmax, &ymax);
    // printf("xmin : %.2f  ymin : %.2f xmax : %.2f ymax : %.2f \n", xmin, ymin, xmax, ymax);

    Reseau *R = reconstitueReseauArbre(C);
    FILE *f2 = fopen("resArbre.txt", "w");
    ecrireReseau(R, f2);

    libererChaines(C);
    fclose(f);
    return 0;
}
