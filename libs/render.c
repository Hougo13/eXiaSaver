//
// Created by hougo on 07/12/16.
//

#include "render.h"


canevas extractFile(char *name)
{
    /* On initialise les 2 valeurs de bases qui serviront dans les boucles For */
    int i;
    int j;

    /* On initialise les valeurs qui vont récupérer les données dans les fichiers */
    int lignes;
    int colonnes;

    int magic;/* Valeur du nombre magic (P est général, on n'en a donc pas besoin) */



    /* On initialise l'ouverture du fichier en fonction du nom qui est entré dans la fonction */
    FILE* fichier = NULL;
    fichier = fopen(name, "r+");

    /* On "saute" le caractère "P" car inutile */
    fgetc(fichier);

    /* On récupère le nombre magic*/
    fscanf(fichier, "%d", &magic);

    /* On récupère les valuers des lignes et des colonnes */
    fscanf(fichier, "%d %d", &colonnes, &lignes);

    /* On créé une variable de type de notre structure */
    canevas result;

    /* On initialise les valeurs de notre variable de type structure */
    result.colonnes = colonnes;
    result.lignes = lignes;
    result.magic = magic;
    strcpy(result.nom, name);

    /* On alloue de manière dynamique notre tableau de pointeurs */
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

    printf("nom: %s\n", result.nom);
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
    }

    /* On ferme le fichier*/
    fclose(fichier);

    /* On retourne notre variable de type structure*/
    return result;
}
