#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/controller2.c"

void main(int argc, char *argv[])
{
    char **urls;
    int auto_refresh;
    int sec = 0;
    char text[64];

    char *sl = getenv("EXIASAVER2_SLEEP");
    if(sl == NULL || sl[0]=='\0'){
        auto_refresh = 5;
    } else{
        auto_refresh = atoi(sl);
    }

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