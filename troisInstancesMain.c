#include "comparaisons.h"
#include <time.h>

int main()// Q6.1
{
    // Instance 1
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
    f2 = fopen("00014_burmaListe.txt", "w");
    t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(L);
    
    // Reconstruction par table hachage
    Reseau *H = NULL;
    f2 = fopen("00014_burmaHachage.txt", "w");
    for(int i = 1; i < 20; i+=4){
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

    // // Instance 2
    // // lecture et creation d'une instance de Chaines et de Reseau
    // f = fopen("05000_USA-road-d-NY.cha", "r");
    // c = lectureChaines(f);
    // fclose(f);

    // // construction du reseau, hachage et arbre
    // // avec calcul du temps, et son ecriture dans un fichier
    // start = clock();
    // L = reconstitueReseauListe(c);
    // end = clock();
    // f2 = fopen("05000_USA-road-d-NYListe.txt", "w");
    // t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
    // fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    // fclose(f2);
    // liberation_reseau(L);
    
    // // Reconstruction par table hachage
    // H = NULL;
    // f2 = fopen("05000_USA-road-d-NYHachage.txt", "w");
    // for(int i = 1; i < 20; i+=4){
    //     start = clock();
    //     H = reconstitueReseauHachage(c, i);
    //     end = clock();
    //     t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
    //     fprintf(f2, "%d %lf\n", i, t_diff);
    //     liberation_reseau(H);
    // }
    // fclose(f2);
    
    // // Reconstruiction par Arbre
    // start = clock();
    // A = reconstitueReseauArbre(c);
    // end = clock();
    // f2 = fopen("05000_USA-road-d-NYArbreQuat.txt", "w");
    // t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
    // fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    // fclose(f2);
    // liberation_reseau(A);


    // // liberation de memoire
    // liberer_chaines(c);

    // Instance 3
    // lecture et creation d'une instance de Chaines et de Reseau
    f = fopen("07397_pla.cha", "r");
    c = lectureChaines(f);
    fclose(f);

    // construction du reseau, hachage et arbre
    // avec calcul du temps, et son ecriture dans un fichier
    start = clock();
    L = reconstitueReseauListe(c);
    end = clock();
    f2 = fopen("07397_plaListe.txt", "w");
    t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(L);
    
    // Reconstruction par table hachage
    H = NULL;
    f2 = fopen("07397_plaHachage.txt", "w");
    for(int i = 1; i < 20; i+=4){
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
    A = reconstitueReseauArbre(c);
    end = clock();
    f2 = fopen("07397_plaArbreQuat.txt", "w");
    t_diff = (double)(end - start)/(CLOCKS_PER_SEC);
    fprintf(f2, "temps de calcusls: %lf\n", t_diff);
    fclose(f2);
    liberation_reseau(A);


    // liberation de memoire
    liberer_chaines(c);

    return 0;
}