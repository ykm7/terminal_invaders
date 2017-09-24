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

#include "aliens.h"
#include "c_window.h"
#include "bullets.h"

#ifndef SPACE_INVADERS_MAIN_H
#define SPACE_INVADERS_MAIN_H

#define DELAY           100000
#define MESSAGE_DELAY   5
#define MAX_BULLETS     200
#define MAX_ALIENS      100

#define TRUE 1
#define FALSE 0

#define ALIEN 1
#define SHIP 0

struct Ship {
    char body;
    int health;
    int posX;
    int posY;
};

struct Bullet {
    char body;
    int curr_x;
    int curr_y;
    int active;
    int type;
};

struct Bullets {
    struct Bullet *bullets[MAX_BULLETS];
    int maxBullets;
    int numBullets;
    int current;
};

extern int level_difficulty;

struct Ship* setupShip(int, int, int);
void destroyShip(struct Ship *);

#endif //SPACE_INVADERS_MAIN_H
