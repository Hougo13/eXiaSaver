//
// Created by hougo on 08/12/16.
//

#include "controller1.h"
#include "render.c"
#include <string.h>

int imgLoad(char *url){
    canevas img = extractFile(url);

    canevas_pos_list array;
    array.size = 1;

    array.data = malloc(sizeof(canevas_pos));

    array.data[0].img = img;
    array.data[0].x = 0;
    array.data[0].y = 0;

    /*array.data[1].img = img;
    array.data[1].x = -3;
    array.data[1].y = 0;*/

    canevas result = canevasGenerator(20, 30, array);

    //grid g = gridGenerator(result);

    printCanevas(result, 1);
}

char *imgUrl(char *name){

    char *url;

    char *path = getenv("EXIASAVER1_PBM");
    if(path == NULL || path[0]=='\0'){
        path = "img/Static/";
    }

    url = malloc(strlen(path) + strlen(name));

    sprintf(url, "%s%s", path, name);

    return url;
}