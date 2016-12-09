//
// Created by hougo on 08/12/16.
//

#include <stdio.h>
#include <stdlib.h>
#include "../libs/controller1.c"

int main(int argc, char *argv[]) {

    if(argc == 0){
        exit(0);
    }

    char *url = imgUrl(argv[1]);
    printf("%s", url);
    imgLoad(url);

    return 0;
}
