//
// Created by yoakim on 26/09/17.
//

#include <ncurses.h>

#include "../include/ship.h"
#include "../include/main.h"

/**
 * Creates a basic ship.
 */
Ship* initialiseShip(int health, int intX, int intY){
    Ship* ship = (Ship*)malloc(sizeof(Ship));
    ship->body = 'A';
    ship->health = health;
    ship->posX = intX / 2;
    ship->posY = intY - 1;
    return ship;
}

void destroyShip(Ship **ship){
    free(*ship);
    *ship = NULL;
}
