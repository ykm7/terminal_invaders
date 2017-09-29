//
// Created by yoakim on 24/09/17.
//

#include "../include/main.h"
#include "../include/aliens.h"

Aliens* initialiseAliens(const int numAliens) {

    Aliens* aliens = NULL;
    if(numAliens > 0){
        aliens = (Aliens *)malloc(sizeof(Aliens));
        aliens->totalNumAliens = numAliens;
        aliens->aliensRemaining = aliens->totalNumAliens;
        aliens->aliensWin = false;
        for(int i = 0; i < aliens->totalNumAliens; i++){
            aliens->aliens[i] = (Alien*)malloc(sizeof(Alien));
            aliens->aliens[i]->body = 'X';
            aliens->aliens[i]->curr_x = i + 1;
            aliens->aliens[i]->curr_y = 1;
            aliens->aliens[i]->direction = 1;
            aliens->aliens[i]->value = 25;
            aliens->aliens[i]->dead = false;
        }
//        }
    }
    return aliens;
}

/**
 * Used during resetting the levels.
 * @param aliens
 */
void setupAliens(Aliens *aliens){
    aliens->aliensRemaining = aliens->totalNumAliens;
    aliens->aliensWin = false;
    for(int i = 0; i < aliens->totalNumAliens; i++){
        aliens->aliens[i]->body = 'X';
        aliens->aliens[i]->curr_x = i + 1;
        aliens->aliens[i]->curr_y = 1;
        aliens->aliens[i]->direction = 1;
        aliens->aliens[i]->value = 25;
        aliens->aliens[i]->dead = false;
    }
}

void destroyAliens(Aliens **aliens){
    if((*aliens) != NULL){
        for(int i = 0; i < (*aliens)->totalNumAliens; i++){
            free((*aliens)->aliens[i]);
            (*aliens)->aliens[i] = NULL;
        }
        free(*aliens);
        *aliens = NULL;
    }
}

/**
 * Returns 1 when the aliens reach the bottom layer.
 * @param aliens
 * @param win_field
 * @param curr_y_pos
 * @param curr_x_pos
 * @return
 */
void moveAliens(Aliens *aliens, Bullets *bullets, int field_start_x, int field_end_x, int field_end_y, int *level){
    for(int i = 0; i < aliens->totalNumAliens; i++){
        if(aliens->aliens[i]->dead != true){

            aliens->aliens[i]->curr_x += aliens->aliens[i]->direction;

            if(aliens->aliens[i]->curr_x <= field_start_x ||
               aliens->aliens[i]->curr_x >= field_end_x){
                aliens->aliens[i]->curr_y++;
                aliens->aliens[i]->direction *= -1;
            }

            // Aliens shooting should increase as the levels progress.
            if((rand() % LEVEL_DIFFICULTY) <= *level){
                shoot(bullets, aliens->aliens[i]->curr_y, aliens->aliens[i]->curr_x, ALIEN);
            }

            // Checking when aliens hit the floor.
            if(aliens->aliens[i]->curr_y >= field_end_y - 2){
                aliens->aliensWin = true;
                break;
            }
        }
    }
}

void killAlien(Alien *alien, int *const score){
    alien->dead = true;
    alien->direction = 0;
    alien->body = ' ';
    (*score) += alien->value;
}
