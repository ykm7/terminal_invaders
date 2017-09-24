//
// Created by yoakim on 24/09/17.
//

#ifndef SPACE_INVADERS_BULLETS_H
#define SPACE_INVADERS_BULLETS_H

#include "main.h"

void displayBullets(WINDOW*, struct Bullets *);
struct Bullets* setupBullets(void);
void shoot(struct Bullets *, int, int, int);
void moveBullets(struct Bullets *, int, int);
void destroyBullets(struct Bullets *);
#endif //SPACE_INVADERS_BULLETS_H
