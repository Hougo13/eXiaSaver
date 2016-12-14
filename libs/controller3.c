//
// Created by hougo on 13/12/16.
//

#include "controller3.h"
#include "../libs/render.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *imgUrl(char *name) {

    char *url;

    char *path = getenv("EXIASAVER3_PBM");
    if (path == NULL || path[0] == '\0') {
        path = "img/Interactif/";
    }

    url = malloc(strlen(path) + strlen(name));

    sprintf(url, "%s%s", path, name);

    return url;
}

void printPlane(int x, int y, direction d){

    char *url = imgUrl(getName(d));

    canevas_pos plane;
    plane.img = readFile(url);
    plane.x = x;
    plane.y = y;

    canevas_pos_list pl;
    pl.size = 1;
    pl.data = malloc(sizeof(canevas_pos));
    pl.data[0] = plane;

    //canevas img = canevasGenerator(40, 80, pl);
    canevas img = canevasFullscreenGenerator(pl);
    grid g =  gridGenerator(img, 0);
    printGrid(g);
    //printCanevas(img, 0);

    saveCoord(x, y);

}

void watchPlane(int x, int y, direction d){
    char c;
    do{
        switch (c){
            case 'z':
                d = UP;
                break;
            case 'q':
                d = LEFT;
                break;
            case 'd':
                d = RIGHT;
                break;
            case 's':
                d = DOWN;
                break;
            case 'x':
                system("clear");
                exit(EXIT_SUCCESS);
        }
        switch (d){
            case UP:
                y--;
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case DOWN:
                y++;
                break;
        }
        printPlane(x, y, d);
    }while (c = getchar());
}

char *getName(direction d){
    char *name;
    switch (d){
        case UP:
            name = "pla_up.pbm";
            break;
        case DOWN:
            name = "pla_down.pbm";
            break;
        case LEFT:
            name = "pla_left.pbm";
            break;
        case RIGHT:
            name = "pla_right.pbm";
            break;
    }
    return name;
}

void saveCoord(int coordX, int coordY){

    FILE* fichier = NULL;
    
    fichier = fopen("cache/coord_plane.txt", "r+");
    fprintf(fichier, "%d %d", coordX, coordY);
    fclose(fichier);


}