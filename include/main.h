//
// Created by yoakim on 22/09/17.
//

#ifndef SPACE_INVADERS_MAIN_H
#define SPACE_INVADERS_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

#define DELAY           75000
#define MESSAGE_DELAY   5

/**
 * Decrease to increase difficulty.
 * Linked to chance that aliens shoot.
 */
#define LEVEL_DIFFICULTY 100

#endif //SPACE_INVADERS_MAIN_H
