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
    double t_diff;
    FILE* f2 = NULL;

    start = clock();
    Reseau *L = reconstitueReseauListe(c);
    end = clock();
    f2 = fopen("timeListe.txt", "w");
    t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(L);
    
    // Reconstruction par table hachage
    Reseau *H = NULL;
    f2 = fopen("timeHachage.txt", "w");
    for(int i = 1; i < 20; i++){
        start = clock();
        H = reconstitueReseauHachage(c, i);
        end = clock();
        t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
        fprintf(f2, "%d %lf\n", i, t_diff);
        liberation_reseau(H);
    }
    fclose(f2);
    
    // Reconstruiction par Arbre
    start = clock();
    Reseau* A = reconstitueReseauArbre(c);
    end = clock();
    f2 = fopen("timeArbre.txt", "w");
    t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(A);


    // liberation de memoire
    liberer_chaines(c);

    FILE *f3 = NULL, *f4 = NULL, *f5 = NULL, *f6 = NULL, *f7 = NULL;
    int nbPointsChaine = 15, xmax = 5000, ymax = 5000;
    int taille_tab_hachage[3] = {10, 100, 1000};
    clock_t debut, fin;
    double temps_calcul = 0;
    Reseau* tmp = NULL;
    f3 = fopen("compListeChainee.txt", "w");
    f4 = fopen("compHachage1.txt", "w");
    f5 = fopen("compHachage2.txt", "w");
    f6 = fopen("compHachage3.txt", "w");
    f7 = fopen("compArbreQuat.txt", "w");
    

    for (int nbChaines = 500; nbChaines <= 5000; nbChaines += 500)
    {
        // generation de Chaines
        c = generationAleatoire(nbChaines, nbPointsChaine, xmax, ymax);

        // reconstruction de reseau par liste chainee
        // ensuite le calcul et l'ecriture de temps utilise
        // enfin liberation de memoire
        debut = clock();
        tmp = reconstitueReseauListe(c);
        fin = clock();
        temps_calcul = (double) ((fin-debut)*1.0/CLOCKS_PER_SEC);
        fprintf(f3, "%d %lf\n", nbChaines*nbPointsChaine, temps_calcul);
        liberation_reseau(tmp);

        // reconstruction de reseau par table de hachage de taille petite
        // ensuite le calcul et l'ecriture de temps utilise
        // enfin liberation de memoire
        debut = clock();
        tmp = reconstitueReseauHachage(c, taille_tab_hachage[0]);
        fin = clock();
        temps_calcul = (double) ((fin-debut)*1.0/CLOCKS_PER_SEC);
        fprintf(f4, "%d %lf\n", nbChaines*nbPointsChaine, temps_calcul);
        liberation_reseau(tmp);

        // reconstruction de reseau par table de hachage de taille moyenne
        // ensuite le calcul et l'ecriture de temps utilise
        // enfin liberation de memoire
        debut = clock();
        tmp = reconstitueReseauHachage(c, taille_tab_hachage[1]);
        fin = clock();
        temps_calcul = (double) ((fin-debut)*1.0/CLOCKS_PER_SEC);
        fprintf(f5, "%d %lf\n", nbChaines*nbPointsChaine, temps_calcul);
        liberation_reseau(tmp);

        // reconstruction de reseau par table de hachage de taille grande
        // ensuite le calcul et l'ecriture de temps utilise
        // enfin liberation de memoire
        debut = clock();
        tmp = reconstitueReseauHachage(c, taille_tab_hachage[0]);
        fin = clock();
        temps_calcul = (double) ((fin-debut)*1.0/CLOCKS_PER_SEC);
        fprintf(f6, "%d %lf\n", nbChaines*nbPointsChaine, temps_calcul);
        liberation_reseau(tmp);

        // reconstruction de reseau par arbre quaternaire
        // ensuite le calcul et l'ecriture de temps utilise
        // enfin liberation de memoire
        debut = clock();
        tmp = reconstitueReseauArbre(c);
        fin = clock();
        temps_calcul = (double) ((fin-debut)*1.0/CLOCKS_PER_SEC);
        fprintf(f7, "%d %lf\n", nbChaines*nbPointsChaine, temps_calcul);
        liberation_reseau(tmp);

        liberer_chaines(c);
    }
    fclose(f3);fclose(f4);fclose(f5);fclose(f6);fclose(f7);
    

    return 0;
}
