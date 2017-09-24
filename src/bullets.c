//
// Created by yoakim on 24/09/17.
//

#include "../include/bullets.h"

void displayBullets(WINDOW* win, struct Bullets *bullets){
    for(int i = 0; i < MAX_BULLETS; i++){
        if(bullets->bullets[i]->active == TRUE){
            mvwprintw(win, bullets->bullets[i]->curr_y, bullets->bullets[i]->curr_x, &(bullets->bullets[i]->body));
        }
    }
}

struct Bullets* setupBullets(void){

    struct Bullets *bullets = (struct Bullets*)malloc(sizeof(struct Bullets));

    bullets->current = 0;
    while(bullets->current < MAX_BULLETS){
        bullets->bullets[bullets->current] = (struct Bullet *)malloc(sizeof(struct Bullet));
        bullets->bullets[bullets->current]->active = FALSE;
        bullets->current++;
    }
    bullets->current = 0;

    return bullets;
}

void shoot(struct Bullets *bullets, int pos_y, int pos_x, int bullet_type){

    bullets->bullets[bullets->current]->active = TRUE;
    bullets->bullets[bullets->current]->curr_x = pos_x;
    bullets->bullets[bullets->current]->curr_y = pos_y;
    bullets->bullets[bullets->current]->body = 'o';
    bullets->bullets[bullets->current]->type = bullet_type;
    bullets->current++;
    if(bullets->current == MAX_BULLETS){
        bullets->current = 0;
    }
}

/**
 * Move bullets up by one.
 * @param bullets
 */
void moveBullets(struct Bullets *bullets, int field_min_y, int field_max_y){

    for(int i = 0; i < MAX_BULLETS; i++) {
        if (bullets->bullets[i]->active == TRUE){

            // Bullets from the ship go 'up'.
            if(bullets->bullets[i]->type == SHIP){
                bullets->bullets[i]->curr_y--;
            }
                // Alien bullets go 'down'
            else if(bullets->bullets[i]->type == ALIEN){
                bullets->bullets[i]->curr_y++;
            }

            if (bullets->bullets[i]->curr_y == field_min_y ||
                bullets->bullets[i]->curr_y == field_max_y) {
                bullets->bullets[i]->active = FALSE;
            }
        }
    }
}

void destroyBullets(struct Bullets *bullets){
    for(int i = 0; i < MAX_BULLETS; i++){
        free(bullets->bullets[i]);
    }
    free(bullets);
}
