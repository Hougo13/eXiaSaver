//
// Created by hougo on 07/12/16.
//

#ifndef EXIASAVER_RENDER_H
#define EXIASAVER_RENDER_H

    //structure contenant une image
    typedef struct {
        int colonnes;
        int lignes;
        char nom[30];
        int **data;
        int magic;
    } canevas;

    //structure contenant une grille à afficher
    typedef struct {
        int colonnes;
        int lignes;
        int **data;
    } grid;

    //structure contenant une image à positionner
    typedef struct {
        int x;
        int y;
        canevas img;
    } canevas_pos;

//structure contenant une liste d'images à positionner
    typedef struct {
        int size;
        canevas_pos *data;
    } canevas_pos_list;

    canevas extractFile(char *name);                                                //permet de generer image à partir d'un ficher pbm

    canevas readFile(char *name);                                                   //meme fonction que extract file mais sans processus fils
    void streamFile(char *name, int *descriptor);                                   //appeler dans le fils qui permet de lire le pbm et l'envoi dans un pipe
    canevas readStream(int *descriptor);                                            //appeler dans le pere, elle lit le pipe et genere le canevas

    grid gridGenerator(canevas final, int centered);                                //genere une grille à partir d'un canevas
    void printGrid(grid g);                                                         //affiche une grille

    canevas canevasFullscreenGenerator(canevas_pos_list array);                     //genere un canevas de la taille du shell à partir de plusieurs
    canevas canevasGenerator(int height, int width, canevas_pos_list array);        //genere un canevas à partir de plusieurs
    canevas mergeCanevas(canevas img, canevas_pos element);                         //fusionne un canevas et un canevas à postionner
    int printCanevas(canevas img, int auto_refresh);                                // affiche un canevas

    int ifPixel(int y, int x, canevas_pos_list array);                              //test si un pixel existe au coord

#endif //EXIASAVER_RENDER_H
