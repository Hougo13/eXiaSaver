//
// Created by hougo on 08/12/16.
//

#include <stdio.h>
#include "../libs/controller2.c"

void main(int argc, char *argv[])
{

	char h[8];
    char **urls;
    int auto_refresh = 1;

    while (1){
        getTime(h);
        urls = getURLs(h);
        printTime(urls);
        sleep(auto_refresh);
    }
}
