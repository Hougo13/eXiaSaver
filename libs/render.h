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
    } canevas;

    typedef struct {
        int colonnes;
        int lignes;
        int **data;
    } grid;

    canevas extractFile(char *name);
    grid gridGenerator(canevas final);

#endif //EXIASAVER_RENDER_H
