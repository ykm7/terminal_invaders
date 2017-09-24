//
// Created by yoakim on 24/09/17.
//

#ifndef SPACE_INVADERS_C_WINDOW_H
#define SPACE_INVADERS_C_WINDOW_H

#include "main.h"

WINDOW *setupWindow(int, int, int, int);
void drawBorders(WINDOW *);
void destroyWin(WINDOW *);
void displayBullets(WINDOW*, struct Bullets *);
void displayScore(WINDOW *, int const *const);
void displayBanner(WINDOW *);
void displayLevel(WINDOW *, int const *const);
void displayHealth(WINDOW *, struct Ship *);
#endif //SPACE_INVADERS_C_WINDOW_H
