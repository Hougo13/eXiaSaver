//
// Created by hougo on 13/12/16.
//

#ifndef EXIASAVER_CONTROLLER3_H
#define EXIASAVER_CONTROLLER3_H

typedef enum {UP, DOWN, RIGHT, LEFT} direction;

char *imgUrl(char *name);
void printPlane(int x, int y, direction d);
void watchPlane(int x, int y, direction d);
char *getName(direction d);

#endif //EXIASAVER_CONTROLLER3_H
