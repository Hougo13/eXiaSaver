//
// Created by hougo on 08/12/16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <dirent.h>
#ifndef WIN32

#endif

#include <time.h>   // pour rand
 
#include <unistd.h> //execv

#include <string.h>


int rand_a_b(int a, int b);

void executor(int, char **global);

int selecteur();

char **transformator (char global[30], int select_transfo);

int main(int argc, char *argv[])
{

    system("clear");
    system("setterm -cursor off");

    int selec;
    int alea;
    char global[30];
    int nb_files = 0;
    int i;

    char* Global;

    char chaine_log[50];
    char chaine_save[50];
    int compt;

    char **tabXtab;

    char coord_final[30];

    char *path;

    char coord_x[30];
    char coord_y[30];

    int ret_x;
    int ret_y;

    //Pointeur pour se déplacer dans les fichiers
    FILE* fichier = NULL;

    printf("Type:\n");
    printf("1. Static\n");
    printf("2. Dynamique\n");
    printf("3. Intéractif\n");
    printf("4. Log\n");



    //On choisit le type de fond ! A passer en aléatoire !
    scanf("%d",&selec); //rand_a_b(1, 4);

    if(argc > 1 )
    {
        if (strcmp(argv[1], "log") == 0)
        {selec = 4;}
    }   


    switch(selec)
    {
        case 1:

           //Recherche du répertoire /img
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

            struct dirent* fichierLu = NULL;

            //Liste des fichiers dans le répertoire /img + comptage
            while ((fichierLu = readdir(rep)) != NULL)
            {
                printf("Le fichier lu s'appelle %s\n", fichierLu -> d_name);
                if(strcmp(fichierLu->d_name, ".") &&  strcmp(fichierLu->d_name, "..")) {
                    nb_files++;
                }
            }

            printf("Il y a %d fichiers\n", nb_files);

            //Allocation dynamique d'un tableau de pointeur de string de la taille du nombre de fichiers
            tabXtab = malloc(sizeof(char*) * nb_files);

            rewinddir(rep);

            i=0;

            //Remplissage du tableau de string en fonction du nom des fichiers (peuvent prendre les noms '.' et '..' qui seront exclus
            while ((fichierLu = readdir(rep)) != NULL)
            {
                if(strcmp(fichierLu->d_name, ".") &&  strcmp(fichierLu->d_name, "..")) {
                    tabXtab[i] = fichierLu->d_name;
                    i++;
                }
            }

            //Affichage des noms à partir du tabeau de pointeurs de string
            for(i=0; i < nb_files; i++)
            {
                printf("Le nom du fichier %d est: %s\n", i, tabXtab[i]);
            }


            //Génération d'un nombre aléatoire
            alea = rand_a_b(1, nb_files+1);
            printf("alea= %d\n", alea);


            //Choix de l'image en fonction du nombre généré
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

            printf("je suis l'ancien global: %s\n", global);
            
            executor(1, transformator(global, 1));

            break;

            
            
        

        case 2:

            strcpy(global, "5x3");

            executor(2, transformator(global, 2));

            break;

        case 3:

            //Ouverture du fichier qui contient les coordonnées de base de l'avion et lecture de celles-ci
            fichier = fopen("cache/coord_plane.txt", "r+");
            fscanf(fichier, "%s %s", &coord_x, &coord_y);
            fclose(fichier);

            printf("coord_x: %s\n", coord_x);
            printf("coord_y: %s\n", coord_y);

            sprintf(coord_final, "%sx%s", coord_x, coord_y);

            executor(3, transformator(coord_final, 3));

            break;

        case 4:
            
            printf("Voici l'historique d'utilisation:\n");
            
            fichier = fopen("cache/log.txt", "r+");

            compt = 0;
            

            while(compt == 0)
            {
                if(strcmp(chaine_save, chaine_log) == 0)
                    compt = 1;

                fgets(chaine_log, 50, fichier);
                printf("%s", chaine_log);
                strcpy(chaine_save, chaine_log);
            }

            fgets(chaine_log, 50, fichier);
            printf("%s\n", chaine_log);
            

            fclose(fichier);
            break;

    }


    


    return 0;
}


int rand_a_b(int a, int b)
{

    srand(time(NULL));
    return rand()%(b-a) +a;
}


void executor(int a, char **global)
{
    
    char log[100];


    time_t temps;
    struct tm instant;

    time(&temps);
    instant =* localtime(&temps);

    sprintf(log, "%d/%d %d || %d:%d:%d || Type: %d {%s}", instant.tm_mday, instant.tm_mon, instant.tm_year + 1900, instant.tm_hour, instant.tm_min, instant.tm_sec, a, global[1]);

    printf("je suis log: %s\n", log);

    FILE* fichier = NULL;
    fichier = fopen("cache/log.txt", "r+");
    while(fgetc(fichier) != EOF);
    fprintf(fichier, "%s\n",log);
    fclose(fichier);



    
    switch(a)
    {
        
        case 1:
            execv("./eXiaSaver1", global);
            break;
        case 2:
            execv("./eXiaSaver2", NULL);
            break;
        case 3:            
            printf("je suis global: %s\n", global[1]);

            execv("./eXiaSaver3", global); 
            break;
    }




}

 char **transformator (char global[30], int select_transfo)
 {
    
    int i;
    int taille;
    char **global_transf;

    global_transf = malloc(sizeof(char*) * 2);


    
    switch(select_transfo)
    {
        case 1:
            global_transf[0] = "./eXiaSaver1";
            break;
        case 2:
            global_transf[0] = "./eXiaSaver2";
            break;
        case 3:
            global_transf[0] = "./eXiaSaver3";
            
            break;
    }   
    
    global_transf[1] = global;

    return global_transf;

 }



