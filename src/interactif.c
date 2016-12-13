//
// Created by hougo on 08/12/16.
//

#include <stdio.h>
#include <stdlib.h>
#include "../libs/controller3.c"

int main(int argc, char *argv[]) {

    if(argc != 2){
        exit(EXIT_FAILURE);
    }

    int x,y;
    sscanf(argv[1], "%dx%d", &x, &y);

    direction d = RIGHT;
    watchPlane(x, y, d);

    return 0;
}
