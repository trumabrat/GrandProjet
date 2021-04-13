#include "comparaisons.h"
#include <time.h>

// Q6.1
// On observe que l'efficacite temporel Liste > TableHachage > ArbreQuat
// Et quand on augemente la taille de la table hachage, le temps de calcul diminue
//  en suite se trouve a un niveau stable
int main()
{
    FILE* f = NULL;
    clock_t start, end;
    double t_diff;
    FILE* f2 = NULL;

    // Instance 1
    // lecture et creation d'une instance de Chaines et de Reseau
    
    f = fopen("00014_burma.cha", "r");
    Chaines *c = lectureChaines(f);
    fclose(f);

    // construction du reseau, hachage et arbre
    // avec calcul du temps, et son ecriture dans un fichier
    start = clock();
    Reseau *L = reconstitueReseauListe(c);
    end = clock();
    f2 = fopen("00014_burmaListe.txt", "w");
    t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(L);
    
    // Reconstruction par table hachage
    Reseau *H = NULL;
    f2 = fopen("00014_burmaHachage.txt", "w");
    for(int i = 2; i < 30; i+=2){
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
    f2 = fopen("00014_burmaArbreQuat.txt", "w");
    t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(A);


    // liberation de memoire
    liberer_chaines(c);

    // Instance 2
    // lecture et creation d'une instance de Chaines et de Reseau
    f = fopen("05000_USA-road-d-NY.cha", "r");
    Chaines* c2 = lectureChaines(f);
    fclose(f);

    // construction du reseau, hachage et arbre
    // avec calcul du temps, et son ecriture dans un fichier
    start = clock();
    Reseau* L2 = reconstitueReseauListe(c2);
    end = clock();
    f2 = fopen("05000_USA-road-d-NYListe.txt", "w");
    t_diff = (double)(end - start)*1.0/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(L2);
    
    // Reconstruction par table hachage
    Reseau* H2 = NULL;
    f2 = fopen("05000_USA-road-d-NYHachage.txt", "w");
    for(int i = 5; i <= 100; i+=5){
        start = clock();
        H2 = reconstitueReseauHachage(c2, i);
        end = clock();
        t_diff = (double)(end - start)*1.0/(CLOCKS_PER_SEC);
        fprintf(f2, "%d %lf\n", i, t_diff);
        liberation_reseau(H2);
    }
    fclose(f2);
    
    // Reconstruiction par Arbre
    start = clock();
    Reseau* A2 = reconstitueReseauArbre(c2);
    end = clock();
    f2 = fopen("05000_USA-road-d-NYArbreQuat.txt", "w");
    t_diff = (double)(end - start)*1.0/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(A2);


    // liberation de memoire
    liberer_chaines(c2);

    // Instance 3
    // lecture et creation d'une instance de Chaines et de Reseau
    f = fopen("07397_pla.cha", "r");
    Chaines* c3 = lectureChaines(f);
    fclose(f);

    // construction du reseau, hachage et arbre
    // avec calcul du temps, et son ecriture dans un fichier
    start = clock();
    Reseau* L3 = reconstitueReseauListe(c3);
    end = clock();
    f2 = fopen("07397_plaListe.txt", "w");
    t_diff = (double)(end - start)*1.0/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(L3);
    
    // Reconstruction par table hachage
    Reseau* H3 = NULL;
    f2 = fopen("07397_plaHachage.txt", "w");
    for(int i = 10; i <= 1000; i+=10){
        start = clock();
        H3 = reconstitueReseauHachage(c3, i);
        end = clock();
        t_diff = (double)(end - start)*1.0/(CLOCKS_PER_SEC);
        fprintf(f2, "%d %lf\n", i, t_diff);
        liberation_reseau(H3);
    }
    fclose(f2);
    
    // Reconstruiction par Arbre
    start = clock();
    Reseau* A3 = reconstitueReseauArbre(c3);
    end = clock();
    f2 = fopen("07397_plaArbreQuat.txt", "w");
    t_diff = (double)(end - start)*1.0/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(A3);

    // liberation de memoire
    liberer_chaines(c3);

    return 0;
}