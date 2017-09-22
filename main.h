//
// Created by yoakim on 22/09/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#ifndef SPACE_INVADERS_MAIN_H
#define SPACE_INVADERS_MAIN_H

#endif //SPACE_INVADERS_MAIN_H

#define DELAY 150000

/* int *maxY; */
/* int *maxX; */

struct Alien {
    char body;
};

struct Aliens {
    struct Alien **aliens;
    int totalNumAliens;
    int aliensRemaining;
};

struct Ship {
    char body;
    int health;
    int posX;
    int posY;
};

struct Aliens* setupAliens(const int);
struct Ship* setupShip(int, int, int);
WINDOW *setupWindow(int, int, int, int);
void drawBorders(WINDOW *);
void destroyWin(WINDOW *);
void destroyShip(struct Ship *);
void destroyAliens(struct Aliens *);
