//
// Created by yoakim on 24/09/17.
//

#ifndef SPACE_INVADERS_BULLETS_H
#define SPACE_INVADERS_BULLETS_H

#include "bullets.h"

#define MAX_BULLETS     200

#define ALIEN 1
#define SHIP 0

typedef struct bullet {
    char body;
    int curr_x;
    int curr_y;
    int active;
    int type;
} Bullet;

typedef struct bullets {
    Bullet *bullets[MAX_BULLETS];
//    int maxBullets;
//    int numBullets;
    int current;
} Bullets;

Bullets* initialisingBullets(void);
void setupBullets(Bullets *);
void shoot(Bullets *, int, int, int);
void moveBullets(Bullets *, int, int);
void destroyBullets(Bullets **);

#endif //SPACE_INVADERS_BULLETS_H
