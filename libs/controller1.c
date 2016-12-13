//
// Created by hougo on 08/12/16.
//

#include "controller1.h"
#include "render.c"
#include <string.h>

int imgLoad(char *url){

    canevas img = extractFile(url);

    printCanevas(img, 1);
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