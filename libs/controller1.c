//
// Created by hougo on 08/12/16.
//

#include "controller1.h"
#include "render.c"
#include <string.h>

int imgLoad(char *url){
    canevas img = extractFile(url);

    canevas_pos_list array;
    array.size = 2;

    array.data = malloc(sizeof(canevas_pos)*2);

    array.data[0].img = img;
    array.data[0].x = 0;
    array.data[0].y = 0;

    array.data[1].img = img;
    array.data[1].x = 15;
    array.data[1].y = 10;

    canevas result = canevasGenerator(20, 30, array);

    //grid g = gridGenerator(result);

    printCanevas(result);
}

char *imgUrl(char *name){

    char *url;

    char *path = getenv("EXIASAVER1_PBM");
    if(path == NULL || path[0]=='\0'){
        path = "img/Static/";
    }

    url = malloc(sizeof(path)+sizeof(name));

    sprintf(url, "%s%s", path, name);

    return url;
}