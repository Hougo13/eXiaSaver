#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include <string.h>
#include "libs/render.c"
int main(int argc, char *argv[]) {
    char NOM[30];
    printf("Entrez le nom du fichier: ");
    scanf("%s", &NOM);
    extractFile(NOM);
    return 0;
}
