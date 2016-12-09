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
        case_cl = case_ln;
    } else{
        case_ln = case_cl;
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