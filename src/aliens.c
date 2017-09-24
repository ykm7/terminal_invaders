//
// Created by yoakim on 24/09/17.
//

#include "../include/aliens.h"

struct Aliens* setupAliens(const int numAliens) {

    struct Aliens* aliens = (struct Aliens *)malloc(sizeof(struct Aliens));
    aliens->totalNumAliens = numAliens;
    aliens->aliensRemaining = numAliens;
    aliens->aliensWin = FALSE;
    for(int i = 0; i < numAliens; i++){
        aliens->aliens[i] = (struct Alien*)malloc(sizeof(struct Alien) * numAliens);
        aliens->aliens[i]->body = 'X';
        aliens->aliens[i]->curr_x = i + 1;
        aliens->aliens[i]->curr_y = 1;
        aliens->aliens[i]->direction = 1;
        aliens->aliens[i]->value = 25;
        aliens->aliens[i]->dead = FALSE;
    }
    return aliens;
}

void destroyAliens(struct Aliens *aliens){
    for(int i = 0; i < aliens->totalNumAliens; i++){
        free(aliens->aliens[i]);
    }
    free(aliens->aliens);
    free(aliens);
}

/**
 * Returns 1 when the aliens reach the bottom layer.
 * @param aliens
 * @param win_field
 * @param curr_y_pos
 * @param curr_x_pos
 * @return
 */
void moveAliens(struct Aliens *aliens, struct Bullets *bullets, int field_start_x, int field_end_x, int field_end_y){
    for(int i = 0; i < aliens->totalNumAliens; i++){
        if(aliens->aliens[i]->dead != TRUE){

            aliens->aliens[i]->curr_x += aliens->aliens[i]->direction;

            if(aliens->aliens[i]->curr_x <= field_start_x ||
               aliens->aliens[i]->curr_x >= field_end_x){
                aliens->aliens[i]->curr_y++;
                aliens->aliens[i]->direction *= -1;
            }

            // Aliens shooting should increase as the levels progress.
            if((rand() % level_difficulty) == 1){
                shoot(bullets, aliens->aliens[i]->curr_y, aliens->aliens[i]->curr_x, ALIEN);
            }

            // Checking when aliens hit the floor.
            if(aliens->aliens[i]->curr_y >= field_end_y - 2){
                aliens->aliensWin = TRUE;
                break;
            }
        }
    }
}

void displayAliens(WINDOW *win_field, struct Aliens *aliens){
    for(int i = 0; i < aliens->totalNumAliens; i++) {
        mvwprintw(win_field, aliens->aliens[i]->curr_y, aliens->aliens[i]->curr_x, &(aliens->aliens[i]->body));
    }
}

void killAlien(struct Alien *alien, int *const score){
    alien->dead = TRUE;
    alien->direction = 0;
    alien->body = ' ';
    (*score) += alien->value;
}
