//
// Created by hougo on 08/12/16.
//

#include "controller1.h"
#include "render.c"
#include <string.h>

int imgLoad(char *url){
    canevas img = extractFile(url);
    printCanevas(img);
}

char *imgUrl(char *name){

    char *url;

    char *path = getenv("EXIASAVER1_PBM");
    if(path == NULL || path[0]=='\0'){
        path = "img/";
    }

    url = malloc(sizeof(path)+sizeof(name));

    sprintf(url, "%s%s", path, name);

    return url;
}