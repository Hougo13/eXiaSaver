//
// Created by hougo on 08/12/16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int rand_a_b(int, int);

int main(int argc, char *argv[]) {

    system("cls");

    int selec;
    int alea;
    char global[30];

    int coord_x;
    int coord_y;

    printf("Entrez le numero du type:\n");
    printf("1. Static\n");
    printf("2. Dynamique\n");
    printf("3. Interactif\n");

    scanf("%d", &selec);

    switch(selec)
    {
        case 1:

            alea = rand_a_b(0, 2);

            printf("alea= %d\n", alea);

            switch(alea)
            {
                case 0:
                    strcpy(global, "img0.txt");
                    break;
                case 1:
                    strcpy(global, "img1.txt");
                    break;
                default:
                    break;
            }


            //exec fichier1
            //envoyer global

            break;

        case 2:

            //exec fichier2

            break;

        case 3:
            FILE* fichier = NULL;
            fichier = fopen("coord_plane.txt", "r+");

            fscanf(fichier, "%d %d", &coord_x, &coord_y);

            fclose("coord_plane.txt");

            //exec fichier3
            //envoyer coord_x et coord_y

            printf("coord_x: %", coord_x);
            printf("coord_y: %", coord_y);


            break;




        default:
            break;

    }

    return 0;
}


int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}
