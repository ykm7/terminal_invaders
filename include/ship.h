//
// Created by yoakim on 26/09/17.
//

#ifndef SPACE_INVADERS_SHIP_H
#define SPACE_INVADERS_SHIP_H

typedef struct {
    char body;
    int health;
    int posX;
    int posY;
} Ship;

Ship* setupShip(int, int, int);
void destroyShip(Ship *);

#endif //SPACE_INVADERS_SHIP_H
