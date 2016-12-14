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

    /*
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

    }*/
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
/*
    int saveSTDOUT;
    close(descriptor[1]);
    saveSTDOUT = dup(STDOUT_FILENO);
    //dup2(descriptor[0], STDOUT_FILENO);
    //close(descriptor[0]);

    // On initialise les 2 valeurs de bases qui serviront dans les boucles For
    int i;
    int j;

    // On initialise les valeurs qui vont r�cup�rer les donn�es dans les fichiers
    int lignes;
    int colonnes;

    int magic;/* Valeur du nombre magic (P est g�n�ral, on n'en a donc pas besoin)

    // On initialise l'ouverture du fichier en fonction du nom qui est entr� dans la fonction
    FILE* fichier = NULL;

    fichier = fopen(name, "r+");

    dup2(fichier, descriptor[0]);
    // On "saute" le caract�re "P" car inutile
    fgetc(fichier);

    // On r�cup�re le nombre magic
    fscanf(fichier, "%d", &magic);
    printf("%d", magic);

    //On r�cup�re les valuers des lignes et des colonnes
    fscanf(fichier, "%d %d", &colonnes, &lignes);
    printf("%d %d", colonnes, lignes);

    //On cr�� une variable de type de notre structure
    canevas result;

    //On initialise les valeurs de notre variable de type structure
    result.colonnes = colonnes;
    result.lignes = lignes;
    result.magic = magic;
    strcpy(result.nom, name);

    //On alloue de mani�re dynamique notre tableau de pointeurs
    result.data = malloc(sizeof(int*) * lignes);

    for(i=0; i < lignes; i++)
    {
        result.data[i] = malloc(sizeof(int) * colonnes);
    }

    //On stocke dans notre tableau de pointeurs les valeurs binaires de notre fichier
    for(i=0; i < lignes; i++)
    {
        for(j=0; j < colonnes; j++)
        {
            fscanf(fichier, "%d", &result.data[i][j]);
        }
    }

    // On ferme le fichier
    fclose(fichier);

    dup2(saveSTDOUT, STDOUT_FILENO);*/
}

canevas readStream(int descriptor[2]){
    /*int saveSTDIN;
    close(descriptor[1]);
    saveSTDIN = dup(STDIN_FILENO);
    dup2(descriptor[0], STDIN_FILENO);

    canevas img;

    scanf("%d", img.magic);
    scanf("%d %d", img.colonnes, img.lignes);

    dup2(saveSTDIN, STDIN_FILENO);
    return img;*/
}

grid gridGenerator(canevas final, int centered){
    //on declare la nouvelle grille
    int canevas_cl, canevas_ln, case_cl, case_ln, current_cl, current_ln, margin_ln, margin_cl, bit_state;
    grid g;

    //On recup le taille su shell
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    if(w.ws_col < final.colonnes*2 || w.ws_row-1 < final.lignes){
        printf("Shell trop petit ! %dx%d %dx%d", w.ws_col, w.ws_row-1, final.colonnes, final.lignes);
        exit(EXIT_FAILURE);
    }

    //printf("(%d,%d)->%d\n", w.ws_row, (final.lignes - 1),w.ws_row < (final.lignes - 1));

    if (centered == 1){
        g.colonnes = w.ws_col;
        g.lignes = w.ws_row - 1;
    } else {
        g.colonnes = final.colonnes*2;
        g.lignes = final.lignes;
    }
    g.data = malloc(sizeof(int*) * g.lignes);

    //On stocke le nombre de ligne et colonne dans le canevas
    canevas_cl = final.colonnes;
    canevas_ln = final.lignes;

    //On stocke le nombre de ligne et colonne d'une case du canevas
    case_ln = g.lignes/canevas_ln;
    case_cl = g.colonnes/canevas_cl;
    //printf("(%d,%d)(%d,%d)(%d,%d)(%d,%d)\n", w.ws_row, w.ws_col, final.lignes, final.colonnes, g.lignes, g.colonnes, canevas_ln, canevas_cl);

    //Conserve le ratio x/y
    if(case_ln <= case_cl){
        case_cl = case_ln*2;
    } else if(case_cl < case_ln){
        case_ln = case_cl/2;
    }

    //On stocke le nombre de ligne et colonne de marge pour centrer
    if(centered == 1){
        margin_cl = (g.colonnes - case_cl * canevas_cl)/2;
        margin_ln = (g.lignes - case_ln * canevas_ln)/2;
    }else{
        margin_cl = 0;
        margin_ln = 0;
    }

    //printf("(%d,%d)\n", case_ln, case_cl);
    for(int y=0; y < g.lignes; y++){
        g.data[y] = malloc(sizeof(int) * g.colonnes);
        for(int i = 0 ; i < g.colonnes; i++) {
            //On test dans quel case on se situe
            current_ln = (y - margin_ln) / case_ln;
            current_cl = (i - margin_cl) / case_cl;

            g.data[y][i] = 0;

            //on test si on est dans le canevas et hors des marge
            if (current_cl < canevas_cl && current_ln < canevas_ln && y >= margin_ln && i >= margin_cl) {
                if (final.data[current_ln][current_cl]) {
                    g.data[y][i] = 1;
                }
            }
        }
    }
    return g;
}

int printCanevas(canevas img, int auto_refresh){
    grid g, prev_g;

    if (auto_refresh == 0){
        g = gridGenerator(img, 1);
        printGrid(g);
    }else{
        while(1){
            g = gridGenerator(img, 1);
            if(g.colonnes != prev_g.colonnes || g.lignes != prev_g.lignes){
                printGrid(g);
            }
            prev_g = g;
            sleep(auto_refresh);
        }
    }

}

void printGrid(grid g){

    system("clear");

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

canevas canevasFullscreenGenerator(canevas_pos_list array){
    //On recup le taille su shell
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    int colonnes = w.ws_col/2;
    int lignes = w.ws_row-1;

    return canevasGenerator(lignes, colonnes, array);
}

canevas canevasGenerator(int height, int width, canevas_pos_list array){
    canevas img;
    img.lignes = height;
    img.colonnes = width;
    img.data = malloc(sizeof(int*)*height);

    for (int y = 0; y < height; y++) {
        img.data[y] = malloc(sizeof(int)*width);
        for (int x = 0; x < width; x++) {
            img.data[y][x] = 0;
        }
    }

    for(int i = 0; i < array.size; i++){
        img = mergeCanevas(img, array.data[i]);
    }

    /*for (int y = 0; y < height; y++) {
        img.data[y] = malloc(sizeof(int)*width);
        for (int x = 0; x < width; x++) {
            img.data[y][x] = ifPixel(y,x,array);
            printf("%d", img.data[y][x]);
        }
        printf("\n");
    }*/
    return img;
}

int ifPixel(int y, int x, canevas_pos_list array){
    int value = 0;
    canevas_pos current;
    for (int i = 0; i < array.size; i++){
        current = array.data[i];
        if(y >= current.y && x >= current.x){
            if(y < current.img.lignes + current.y && x < current.img.colonnes + current.x){
                if(current.img.data[y-current.y][x-current.x] == 1)
                    value = 1;
            }
        }
    }
    return value;
}

canevas mergeCanevas(canevas img, canevas_pos element){
    int cx, cy;
    for (int y = 0; y < element.img.lignes; y++) {
        for (int x = 0; x < element.img.colonnes; x++) {
            if (element.img.data[y][x] == 1){
                cy = y + element.y;
                cx = x + element.x;
                while (cy >= img.lignes){
                    cy = cy - img.lignes;
                }
                while (cx >= img.colonnes){
                    cx = cx - img.colonnes;
                }
                while (cy < 0){
                    cy = cy + img.lignes;
                }
                while (cx < 0){
                    cx = cx + img.colonnes;
                }
                img.data[cy][cx] = 1;
            }
        }
    }
    return img;
}