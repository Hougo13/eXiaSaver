//
// Created by hougo on 07/12/16.
//

#include "render.h"


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

    /*printf("nom: %s\n", result.nom);
    printf("numero magic: P%d\n", result.magic);
    printf("colonnes: %d\n", result.colonnes);
    printf("lignes: %d\n", result.lignes);


    printf("\n");

    for(i=0; i < lignes; i++)
    {
        for(j=0; j < colonnes; j++)
        {
            printf("%d", result.data[i][j]);
        }
        printf("\n");
    }*/

    /* On ferme le fichier*/
    fclose(fichier);

    /* On retourne notre variable de type structure*/
    return result;
}

grid gridGenerator(canevas final){

    //On recup le taille su shell
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    int canevas_cl, canevas_ln, case_cl, case_ln, current_cl, current_ln, margin_ln, margin_cl;
    char symbol;

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
        for(int i = 0 ; i < w.ws_col; i++) {
            //On test dans quel case on se situe
            current_ln = (y - margin_ln) / case_ln;
            current_cl = (i - margin_cl) / case_cl;

            symbol = ' ';

            //on test si on est dans le canevas et hors des marge
            if (current_cl < canevas_cl && current_ln < canevas_ln && y > margin_ln && i > margin_cl) {
                if (final.data[current_ln][current_cl]) {
                    symbol = (char) 219;
                }
            }
            printf("%c", symbol);
        }
        printf("\n");
    }

    getchar();
}