//
// Created by hougo on 08/12/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/controller2.c"

void main(int argc, char *argv[])
{
    char **urls;
    int auto_refresh = 5;
    int sec = 0;
    char text[64];

    strcpy(text, "Cet écran sera actualisé dans quelques secondes");
    urls = getURLs(getTime());

    printf("%d\n", sec);
    while(1){
        if (auto_refresh == sec){
            urls = getURLs(getTime());
            sec = 0;
        }
        printTime(urls);
        printText(text);
        for (int i = 0; i < sec; ++i) {
            printf(".");
        }
        fflush(stdout);
        sec++;
        sleep(1);
    }
}