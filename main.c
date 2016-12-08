#include <stdio.h>

#include "libs/render.c"
#include "libs/controllers.h"

int main(int argc, char *argv[]) {
    char NOM[30];
    printf("Entrez le nom du fichier: ");
    scanf("%s", &NOM);
    gridGenerator(extractFile(NOM));
    getchar();
    return 0;
}
