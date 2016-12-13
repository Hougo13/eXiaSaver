#include "controller1.h"
#include <time.h>


int imgLoad(char *url){
    canevas img = extractFile(url);
    printCanevas(img);
}

char *imgUrl(char *name){

    char *url;

    char *path = getenv("EXIASAVER1_PBM");
    if(path == NULL || path[0]=='\0'){
        path = "img/Dynamic/";
    }

    url = malloc(sizeof(path)+sizeof(name));

    sprintf(url, "%s%s", path, name);