//
// Created by yoakim on 24/09/17.
//

#ifndef SPACE_INVADERS_ALIENS_H
#define SPACE_INVADERS_ALIENS_H

#include "bullets.h"
#include "main.h"

#define MAX_ALIENS      100

typedef struct alien {
    char body;
    int curr_x;
    int curr_y;
    int direction;
    int value;
    int dead;
} Alien;

typedef struct aliens {
    Alien *aliens[MAX_ALIENS];
    int totalNumAliens;
    int aliensRemaining;
    int aliensWin;
} Aliens;

Aliens* setupAliens(const int);
void destroyAliens(Aliens **);
void moveAliens(Aliens *,Bullets *, int, int, int, int);
void killAlien(Alien *, int *const);

#endif //SPACE_INVADERS_ALIENS_H
