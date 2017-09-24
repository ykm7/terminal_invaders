//
// Created by yoakim on 24/09/17.
//

#ifndef SPACE_INVADERS_ALIENS_H
#define SPACE_INVADERS_ALIENS_H

#include "main.h"

struct Alien {
    char body;
    int curr_x;
    int curr_y;
    int direction;
    int value;
    int dead;
};

struct Aliens {
    struct Alien *aliens[MAX_ALIENS];
    int totalNumAliens;
    int aliensRemaining;
    int aliensWin;
};

struct Aliens* setupAliens(const int);
void destroyAliens(struct Aliens *);
void moveAliens(struct Aliens *, struct Bullets *, int, int, int);
void displayAliens(WINDOW *, struct Aliens *);
void killAlien(struct Alien *, int *const);

#endif //SPACE_INVADERS_ALIENS_H
