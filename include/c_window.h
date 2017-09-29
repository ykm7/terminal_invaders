//
// Created by yoakim on 24/09/17.
//

#ifndef SPACE_INVADERS_C_WINDOW_H
#define SPACE_INVADERS_C_WINDOW_H

#include <ncurses.h>

#include "bullets.h"
#include "aliens.h"
#include "ship.h"

WINDOW *setupWindow(int, int, int, int);
void drawBorders(WINDOW *);
void destroyWin(WINDOW *);

void displayBullets(WINDOW*, Bullets *);
void displayAliens(WINDOW *, Aliens *);

void displayScore(WINDOW *, int const *const);
void displayBanner(WINDOW *);
void displayLevel(WINDOW *, int const *const);
void displayHealth(WINDOW *, Ship *);

void displayLevelComplete(WINDOW *, int, int, int const *);
void displayGameOver(WINDOW *, int, int, int const *);
void displayHelp(WINDOW *, int);
#endif //SPACE_INVADERS_C_WINDOW_H
