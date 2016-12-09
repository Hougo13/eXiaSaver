//
// Created by hougo on 07/12/16.
//

#ifndef EXIASAVER_RENDER_H
#define EXIASAVER_RENDER_H

    typedef struct {
        int colonnes;
        int lignes;
        char nom[30];
        int **data;
        int magic;
    } canevas;

    typedef struct {
        int colonnes;
        int lignes;
        int **data;
    } grid;

    canevas extractFile(char *name);
    grid gridGenerator(canevas final);
    int printCanevas(canevas img);

#endif //EXIASAVER_RENDER_H
