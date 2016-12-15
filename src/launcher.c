//
// Created by hougo on 08/12/16.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>   // pour rand
#include <unistd.h> //execv
#include <string.h>


int rand_a_b(int a, int b);                  //Return un nbr entre a et b
void executor(int id, char **argv);          //execute le prgrm
char **argvGenerator (char *arg, int id);   //genere le argv à passer
char *getName(void);                        //renvoie un nom d'image
char *homePath(void);                       //renvoie le repertoire des exec
char *pbm1Path(void);                       //renvoie le repertoire des images pbm1
char *cachePath(void);                      //renvoie le repertoire du cache
char *coordURL(void);                       //renvoie l'url du fichier coord de l'avion
char *logURL(void);                         //renvoie l'url du fichier log

int main(int argc, char *argv[])
{
    int selec;
    char c, coord_final[30], coord_x[30], coord_y[30];

    //Pointeur pour se déplacer dans les fichiers
    FILE* fichier = NULL;

    //On clear le shell et on suprime le curseur
    system("clear");
    system("setterm -cursor off");

    //on choisi la fonction l'ecran de veille aleatoirement
    selec = rand_a_b(1, 4);
    if(argc > 1 )
    {
        if (strcmp(argv[1], "-l") == 0 || !strcmp(argv[1], "--log")){
            selec = 4;
        } else if (strcmp(argv[1], "-s") == 0 || !strcmp(argv[1], "--static")){
            selec = 1;
        }else if (strcmp(argv[1], "-d") == 0 || !strcmp(argv[1], "--dynamic")){
            selec = 2;
        }else if (strcmp(argv[1], "-i") == 0 || !strcmp(argv[1], "--interactif")){
            selec = 3;
        }else if (strcmp(argv[1], "-h") == 0 || !strcmp(argv[1], "--help"))
        {
            printf("Commandes disponibles:\n");
            
            printf("    -s   --static       Lance le fond d'écran static\n");
            printf("    -d   --dynamic      Lance le fond d'écran dynamique\n");
            printf("    -i   --interactif   Lance le fond d'écran intéractif\n");
            printf("    -l   --log          Affiche les logs\n");
            printf("    -h   --help         Affiche les commandes disponibles\n");

            selec = 0;
        }else {
            printf("Commande non reconnue ajoutez -h\n");
            exit(EXIT_FAILURE);
        }
    }

    switch(selec)
    {
        case 1:
            executor(selec, argvGenerator(getName(), selec));
            break;

        case 2:
            executor(selec, argvGenerator("5x3", selec));
            break;
        case 3:
            //Ouverture du fichier qui contient les coordonnées de base de l'avion et lecture de celles-ci
            fichier = fopen(coordURL(), "r+");
            fscanf(fichier, "%s %s", &coord_x, &coord_y);
            fclose(fichier);

            sprintf(coord_final, "%sx%s", coord_x, coord_y);

            executor(selec, argvGenerator(coord_final, selec));
            break;
        case 4:
            printf("Voici l'historique d'utilisation:\n\n");
            
            fichier = fopen(logURL(), "r+");

            //On parcourt le fichier log pour l'afficher
            do{
                
                c = fgetc(fichier);
                if (c != EOF)
                    printf("%c", c);
            }while (c != EOF);
            
            printf("\n");

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


void executor(int id, char **argv)
{
    char log[100], *url;

    time_t temps;
    struct tm instant;

    time(&temps);
    instant =* localtime(&temps);

    sprintf(log, "%d/%d %d || %.2d:%.2d:%.2d || Type: %d {%s}", instant.tm_mday, instant.tm_mon, instant.tm_year + 1900, instant.tm_hour, instant.tm_min, instant.tm_sec, id, argv[1]);

    url = malloc(strlen(cachePath())+7);
    sprintf(url, "%slog.txt", cachePath());

    FILE* fichier = NULL;
    fichier = fopen(url, "r+");
    printf("%s", url);

    while(fgetc(fichier) != EOF);

    fprintf(fichier, "%s\n",log);

    fclose(fichier);

    //On se postionne dans le repertoire des fichiers exec
    chdir(homePath());

    switch(id)
    {
        case 1:
            execv(argv[0], argv);
            break;
        case 2:
            execv(argv[0], NULL);
            break;
        case 3:
            execv(argv[0], argv);
            break;
    }




}

 char **argvGenerator (char *arg, int id)
 {
    char **argv;

    argv = malloc(sizeof(char*) * 2);
    argv[0] = malloc(strlen(homePath())+12);

    sprintf(argv[0], "./eXiaSaver%d", id);

    argv[1] = arg;

    printf("%s %s\n", argv[0], argv[1]);

    return argv;

 }

char *getName(void){
    char **tabXtab, *path;
    int nb_files = 0, i = 0, alea;

    //Recherche du répertoire /img
    path = pbm1Path();

    DIR* rep = NULL;
    rep = opendir(path);

    if (rep == NULL) // Si le dossier n'a pas pu �tre ouvert
        exit(EXIT_FAILURE);

    struct dirent* fichierLu = NULL;

    //Liste des fichiers dans le répertoire /img + comptage
    while ((fichierLu = readdir(rep)) != NULL)
    {
        //printf("Le fichier lu s'appelle %s\n", fichierLu -> d_name);
        if(strcmp(fichierLu->d_name, ".") &&  strcmp(fichierLu->d_name, "..")) {
            nb_files++;
        }
    }

    //printf("Il y a %d fichiers\n", nb_files);

    //Allocation dynamique d'un tableau de pointeur de string de la taille du nombre de fichiers
    tabXtab = malloc(sizeof(char*) * nb_files);

    rewinddir(rep);

    //Remplissage du tableau de string en fonction du nom des fichiers (peuvent prendre les noms '.' et '..' qui seront exclus
    while ((fichierLu = readdir(rep)) != NULL)
    {
        if(strcmp(fichierLu->d_name, ".") &&  strcmp(fichierLu->d_name, "..")) {
            tabXtab[i] = fichierLu->d_name;
            i++;
        }
    }

    /*//Affichage des noms à partir du tabeau de pointeurs de string
    for(i=0; i < nb_files; i++)
    {
        printf("Le nom du fichier %d est: %s\n", i, tabXtab[i]);
    }*/

    //Génération d'un nombre aléatoire
    alea = rand_a_b(0, nb_files);

    return tabXtab[alea];
}

char *homePath(void){
    char *path;
    path = getenv("EXIASAVER_HOME");
    if(path == NULL || path[0] == '\0')
    {
        path = "";
    }
    return path;
}

char *pbm1Path(void){
    char *path;
    path = getenv("EXIASAVER1_PBM");
    if(path == NULL || path[0] == '\0')
    {
        path = "img/Static/";
    }
    return path;
}

char *cachePath(void){
    char *path;
    path = malloc(strlen(homePath())+6);
    sprintf(path, "%scache/", homePath());

    return path;
}

char *logURL(void){
    char *path;
    path = malloc(strlen(cachePath())+7);
    sprintf(path, "%slog.txt", cachePath());

    return path;
}

char *coordURL(void){
    char *path;
    path = malloc(strlen(cachePath())+15);
    sprintf(path, "%scoord_plane.txt", cachePath());

    return path;
}