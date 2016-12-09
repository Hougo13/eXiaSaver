//
// Created by hougo on 08/12/16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dirent.h>
#ifndef WIN32

#endif

// ! A revoir !
int rand_a_b(int, int);

int main(int argc, char *argv[])
{

    system("clear");

    int selec;
    int alea;
    char global[30];
    int nb_files = 0;
    int i;

    char **tabXtab;


    char *path;

    char coord_x[30];
    char coord_y[30];

    int ret_x;
    int ret_y;

    FILE* fichier = NULL;

    printf("Entrez le numero du type:\n");
    printf("1. Static\n");
    printf("2. Dynamique\n");
    printf("3. Interactif\n");

    scanf("%d", &selec);

    switch(selec)
    {
        case 1:

            path = getenv("EXIASAVER1_PBM");
            if(path == NULL || path[0] == '\0')
            {
                path = "img/Static";
            }

            DIR* rep = NULL;
            rep = opendir(path);

            if (rep == NULL){ /* Si le dossier n'a pas pu �tre ouvert */
                perror("");
                exit(1); }

            /*if (closedir(rep) == -1){  // S'il y a eu un souci avec la fermeture
                perror("");
                exit(-1);
            }*/

            struct dirent* fichierLu = NULL;

            while ((fichierLu = readdir(rep)) != NULL)
            {
                printf("Le fichier lu s'appelle %s\n", fichierLu -> d_name);
                if(strcmp(fichierLu->d_name, ".") &&  strcmp(fichierLu->d_name, "..")) {
                    nb_files++;
                }
            }

            printf("Il y a %d fichiers\n", nb_files);

            tabXtab = malloc(sizeof(char*) * nb_files);

            rewinddir(rep);

            i = 0;

            while ((fichierLu = readdir(rep)) != NULL)
            {
                if(strcmp(fichierLu->d_name, ".") &&  strcmp(fichierLu->d_name, "..")) {
                    tabXtab[i] = fichierLu->d_name;
                    i++;
                }
            }

            /*for(i=0; i <= nb_files; i++)
            {
                strcpy(tabXtab[i], fichierLu -> d_name);
            }*/

            for(i=0; i < nb_files; i++)
            {
                printf("Le nom du fichier %d est: %s\n", i, tabXtab[i]);
            }



            alea = rand_a_b(0, nb_files);
            printf("alea= %d\n", alea);

            switch(alea)
            {
                case 1:
                    strcpy(global, "img_1.pbm");
                    break;
                case 2:
                    strcpy(global, "img_2.pbm");
                    break;
                case 3:
                    strcpy(global, "img_3.pbm");
                    break;
                case 4:
                    strcpy(global, "img_4.pbm");
                    break;
                case 5:
                    strcpy(global, "img_5.pbm");
                    break;
                case 6:
                    strcpy(global, "img_6.pbm");
                    break;
                default:
                    break;
            }

            break;

        case 2:


            break;

        case 3:
            fichier = fopen("coord_plane.txt", "r+");
            fscanf(fichier, "%s %s", &coord_x, &coord_y);
            fclose(fichier);

            printf("coord_x: %s\n", coord_x);
            printf("coord_y: %s\n", coord_y);

            ret_x = putenv(coord_x);
            ret_y = putenv(coord_y);

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
