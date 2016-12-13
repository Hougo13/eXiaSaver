#include "controller2.h"
#include "render.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char *imgUrl(char *name) {

    char *url;

    char *path = getenv("EXIASAVER2_PBM");
    if (path == NULL || path[0] == '\0') {
        path = "img/Dynamic/";
    }

    url = malloc(strlen(path) + strlen(name));

    sprintf(url, "%s%s", path, name);

    return url;
}

void getTime(char h[8]){

    time_t secondes;
    struct tm instant;

    time(&secondes);
    instant =* localtime(&secondes);

    sprintf(h, "%.2d:%.2d:%.2d", instant.tm_hour, instant.tm_min, instant.tm_sec);
}

char **getURLs(char h[8]){
    char **urls;
    urls = malloc(sizeof(char*)*8);

    char *name;

    for (int i = 0; i < 8; i++) {
        name = getName(h[i]);
        urls[i] = imgUrl(name);
        free(name);
    }

    return urls;
}

char *getName(int c){
    char *name;
    switch (c){
        case '0':
            name = strdup("img_0.pbm");
            break;
        case '1':
            name = strdup("img_1.pbm");
            break;
        case '2':
            name = strdup("img_2.pbm");
            break;
        case '3':
            name = strdup("img_3.pbm");
            break;
        case '4':
            name = strdup("img_4.pbm");
            break;
        case '5':
            name = strdup("img_5.pbm");
            break;
        case '6':
            name = strdup("img_6.pbm");
            break;
        case '7':
            name = strdup("img_7.pbm");
            break;
        case '8':
            name = strdup("img_8.pbm");
            break;
        case '9':
            name = strdup("img_9.pbm");
            break;
        case ':':
            name = strdup("img_double.pbm");
            break;
    }
    return name;
}

void printTime(char **urls){

    int posX[8] = {0,4,7,10,14,17,20,24};
    int posY[8] = {0,0,0,0,0,0,0,0};

    canevas_pos_list array;
    array.size = 8;
    array.data = malloc(sizeof(canevas_pos)*8);

    for (int i = 0; i < 8; ++i) {
        canevas_pos element;
        element.img = readFile(urls[i]);
        element.y = posY[i];
        element.x = posX[i];
        array.data[i] = element;
    }

    canevas t = canevasGenerator(5,27, array);
    printCanevas(t, 0);
}