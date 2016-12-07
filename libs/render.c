//
// Created by hougo on 07/12/16.
//

#include "render.h"

grid gridGenerator(canevas final){

    //On recup le taille su shell
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

    int canevas_cl, canevas_ln, case_cl, case_ln, current_cl, current_ln, margin_ln, margin_cl;
    char symbol;

    //On stocke le nombre de ligne et colonne dans le canevas
    canevas_cl = final.colonnes;
    canevas_ln = final.lignes;

    //On stocke le nombre de ligne et colonne d'une case du canevas
    case_ln = w.ws_row/canevas_ln;
    case_cl = w.ws_col/canevas_cl;

    //On stocke le nombre de ligne et colonne de marge pour centrer
    margin_cl = (w.ws_col%canevas_cl)/2;
    margin_ln = (w.ws_row%canevas_ln)/2;

    for(int y=0;y<w.ws_row;y++){
        for(int i = 0 ; i < w.ws_col; i++){
            //On test dans quel case on se situe
            current_ln = (y-margin_cl)/case_ln;
            current_cl = (i-margin_ln)/case_cl;

            symbol = ' ';

            //on test si on est dans le canevas et hors des marge
            if(current_cl < canevas_cl && current_ln < canevas_ln && i > margin_ln && y > margin_cl) {
                if (final.data[current_ln][current_cl]) {
                    symbol = (char)219;
                }
            }
            printf("%c", symbol);
        }
        printf("\n");
    }

    getchar();
}