//
// Created by hougo on 07/12/16.
//

#include "render.h"
#include <string.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>

canevas extractFile(char *name)
{
    pid_t pid;
    int descriptor[2];
    char msg[2];
    char msg2[3];
    int prevst;
    int a, b;
    canevas img;

    if(pipe(descriptor) != 0){
        printf("Erreur pendant la creation du tube\n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    switch (pid){
        case -1:
            printf("Erreur pendant la creation du fils\n");
            exit(EXIT_FAILURE);
        case 0:
            //streamFile(name, descriptor);
            close(descriptor[1]);
            prevst = dup(1);
            dup2(descriptor[0], 1);
            printf("ok");
            dup2(prevst, 1);
            printf("ok2");
            exit(EXIT_SUCCESS);
        default:
            //img = readStream(descriptor);
            close(descriptor[0]);
            prevst = dup(0);
            dup2(descriptor[1], 0);;
            scanf("%s", msg);
            dup2(prevst, 0);
            wait(NULL);
            printf("%s", msg);
            //printf("%d", img.magic, img.colonnes, img.lignes);

    }
    return readFile(name);
}

canevas readFile(char *name){
    /* On initialise les 2 valeurs de bases qui serviront dans les boucles For */
    int i;
    int j;

    /* On initialise les valeurs qui vont r�cup�rer les donn�es dans les fichiers */
    int lignes;
    int colonnes;

    int magic;/* Valeur du nombre magic (P est g�n�ral, on n'en a donc pas besoin) */



    /* On initialise l'ouverture du fichier en fonction du nom qui est entr� dans la fonction */
    FILE* fichier = NULL;
    fichier = fopen(name, "r+");

    /* On "saute" le caract�re "P" car inutile */
    fgetc(fichier);

    /* On r�cup�re le nombre magic*/
    fscanf(fichier, "%d", &magic);

    /* On r�cup�re les valuers des lignes et des colonnes */
    fscanf(fichier, "%d %d", &colonnes, &lignes);

    /* On cr�� une variable de type de notre structure */
    canevas result;

    /* On initialise les valeurs de notre variable de type structure */
    result.colonnes = colonnes;
    result.lignes = lignes;
    result.magic = magic;
    strcpy(result.nom, name);

    /* On alloue de mani�re dynamique notre tableau de pointeurs */
    result.data = malloc(sizeof(int*) * lignes);

    for(i=0; i < lignes; i++)
    {
        result.data[i] = malloc(sizeof(int) * colonnes);
    }

    /* On stocke dans notre tableau de pointeurs les valeurs binaires de notre fichier*/
    for(i=0; i < lignes; i++)
    {
        for(j=0; j < colonnes; j++)
        {
            fscanf(fichier, "%d", &result.data[i][j]);
        }
    }

    /* On ferme le fichier*/
    fclose(fichier);

    /* On retourne notre variable de type structure*/
    return result;
}

void streamFile(char *name, int *descriptor){

    int saveSTDOUT;
    close(descriptor[1]);
    saveSTDOUT = dup(STDOUT_FILENO);
    //dup2(descriptor[0], STDOUT_FILENO);
    //close(descriptor[0]);

    /* On initialise les 2 valeurs de bases qui serviront dans les boucles For */
    int i;
    int j;

    /* On initialise les valeurs qui vont r�cup�rer les donn�es dans les fichiers */
    int lignes;
    int colonnes;

    int magic;/* Valeur du nombre magic (P est g�n�ral, on n'en a donc pas besoin) */

    /* On initialise l'ouverture du fichier en fonction du nom qui est entr� dans la fonction */
    FILE* fichier = NULL;

    fichier = fopen(name, "r+");

    dup2(fichier, descriptor[0]);
    /* On "saute" le caract�re "P" car inutile */
    fgetc(fichier);

    /* On r�cup�re le nombre magic*/
    fscanf(fichier, "%d", &magic);
    printf("%d", magic);

    /* On r�cup�re les valuers des lignes et des colonnes */
    fscanf(fichier, "%d %d", &colonnes, &lignes);
    printf("%d %d", colonnes, lignes);

    /* On cr�� une variable de type de notre structure */
    canevas result;

    /* On initialise les valeurs de notre variable de type structure */
    result.colonnes = colonnes;
    result.lignes = lignes;
    result.magic = magic;
    strcpy(result.nom, name);

    /* On alloue de mani�re dynamique notre tableau de pointeurs */
    result.data = malloc(sizeof(int*) * lignes);

    for(i=0; i < lignes; i++)
    {
        result.data[i] = malloc(sizeof(int) * colonnes);
    }

    /* On stocke dans notre tableau de pointeurs les valeurs binaires de notre fichier*/
    for(i=0; i < lignes; i++)
    {
        for(j=0; j < colonnes; j++)
        {
            fscanf(fichier, "%d", &result.data[i][j]);
        }
    }

    /* On ferme le fichier*/
    fclose(fichier);

    dup2(saveSTDOUT, STDOUT_FILENO);
}

canevas readStream(int descriptor[2]){
    int saveSTDIN;
    close(descriptor[1]);
    saveSTDIN = dup(STDIN_FILENO);
    dup2(descriptor[0], STDIN_FILENO);

    canevas img;

    scanf("%d", img.magic);
    scanf("%d %d", img.colonnes, img.lignes);

    dup2(saveSTDIN, STDIN_FILENO);
    return img;
}

grid gridGenerator(canevas final){

    //on declare la nouvelle grille
    int canevas_cl, canevas_ln, case_cl, case_ln, current_cl, current_ln, margin_ln, margin_cl, bit_state;
    grid g;

    //On recup le taille su shell
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    g.colonnes = w.ws_col;
    g.lignes = w.ws_row;
    g.data = malloc(sizeof(int*) * g.lignes);

    //On stocke le nombre de ligne et colonne dans le canevas
    canevas_cl = final.colonnes;
    canevas_ln = final.lignes;

    //On stocke le nombre de ligne et colonne d'une case du canevas
    case_ln = w.ws_row/canevas_ln;
    case_cl = w.ws_col/canevas_cl;

    //Conserve le ratio x/y
    if(case_ln < case_cl){
        case_cl = case_ln*2;
    } else{
        case_ln = case_cl/2;
    }

    //On stocke le nombre de ligne et colonne de marge pour centrer
    margin_cl = (w.ws_col - case_cl * canevas_cl)/2;
    margin_ln = (w.ws_row - case_ln * canevas_ln)/2;

    for(int y=0; y < w.ws_row; y++){
        g.data[y] = malloc(sizeof(int) * g.colonnes);
        for(int i = 0 ; i < w.ws_col; i++) {
            //On test dans quel case on se situe
            current_ln = (y - margin_ln) / case_ln;
            current_cl = (i - margin_cl) / case_cl;

            g.data[y][i] = 0;

            //on test si on est dans le canevas et hors des marge
            if (current_cl < canevas_cl && current_ln < canevas_ln && y > margin_ln && i > margin_cl) {
                if (final.data[current_ln][current_cl]) {
                    g.data[y][i] = 1;
                }
            }
        }
    }
    return g;
}

int printCanevas(canevas img){
    grid g, prev_g;

    while(1){
        g = gridGenerator(img);
        if(g.colonnes != prev_g.colonnes || g.lignes != prev_g.lignes){
            printGrid(g);
        }
        prev_g = g;
        sleep(1);
    }

}

void printGrid(grid g){

    for(int y = 0; y < g.lignes; y++){

    for(int x = 0; x < g.colonnes; x++){
            if(g.data[y][x]){
                printf("█");
            } else{
                printf(" ");
            }
        }
        printf("\n");
    }
}