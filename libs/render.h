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

    typedef struct {
        int x;
        int y;
        canevas img;
    } canevas_pos;

    typedef struct {
        int size;
        canevas_pos *data;
    } canevas_pos_list;

    canevas extractFile(char *name);

    canevas readFile(char *name);
    void streamFile(char *name, int *descriptor);
    canevas readStream(int *descriptor);

    grid gridGenerator(canevas final, int centered);
    void printGrid(grid g);

    canevas canevasFullscreenGenerator(canevas_pos_list array);
    canevas canevasGenerator(int height, int width, canevas_pos_list array);
    canevas mergeCanevas(canevas img, canevas_pos element);
    int printCanevas(canevas img, int auto_refresh);

    int ifPixel(int y, int x, canevas_pos_list array);

#endif //EXIASAVER_RENDER_H
