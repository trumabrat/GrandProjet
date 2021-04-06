#include "chaine.h"
#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include "comparaisons.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double generateRandomDouble(int maximum){
    //genere un double a 2 chiffres apres la virgule
    int nb = rand()%(maximum*100);
    return (nb * 1.0) / 100.0;
}
Chaines* generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax){
    //La CellChaine qu'on va mettre dans la structure Chaines
    CellChaine *cellChaineMain = NULL;

    //La premiere boucle pour creer nbChaines de chaines
    for (int i = 0; i < nbChaines; i++)
    {
        CellChaine *newCellChaine = calloc(1, sizeof(CellChaine));
        newCellChaine->numero = i;

        //Le CellPoint qu'on va mettre dans CellChaine
        CellPoint *cellPointMain = NULL;

        //La deuxieme boucle pour creer nbPointsChaine pour chaque CellChaine
        for (int j = 0; j < nbPointsChaine; j++)
        {
            CellPoint *newCellPoint = calloc(1,sizeof(CellPoint));

            //attribution des points entre 0 et xmax,ymax (noncompris)
            newCellPoint->x = generateRandomDouble(xmax);
            newCellPoint->y = generateRandomDouble(ymax);

            //En tete de cellPointMain
            newCellPoint->suiv = cellPointMain;
            cellPointMain = newCellPoint;
        }

        //insertions des points dans la CellChaine, puis de la CellChaine dans la tete de cellChaineMain
        newCellChaine->points = cellPointMain;
        newCellChaine->suiv = cellChaineMain;
        cellChaineMain = newCellChaine;
    }

    //Creation de la chaine
    Chaines *C = calloc(1, sizeof(Chaines));
    C->gamma = 1;
    C->nbChaines = nbChaines;
    C->chaines = cellChaineMain;

    return C;
}