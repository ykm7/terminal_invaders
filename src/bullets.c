//
// Created by yoakim on 24/09/17.
//

#include "../include/bullets.h"
#include "../include/main.h"

Bullets* initialisingBullets(void){

    Bullets *bullets = (Bullets*)malloc(sizeof(Bullets));

    bullets->current = 0;
    while(bullets->current < MAX_BULLETS){
        bullets->bullets[bullets->current] = (Bullet *)malloc(sizeof(Bullet));
        bullets->bullets[bullets->current]->active = false;
        bullets->current++;
    }
    bullets->current = 0;

    return bullets;
}

void setupBullets(Bullets *bullets){
    for(int i = 0; i < MAX_BULLETS; i++){
        bullets->bullets[bullets->current]->active = false;
    }
}

void shoot(Bullets *bullets, int pos_y, int pos_x, int bullet_type){

    bullets->bullets[bullets->current]->active = true;
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
void moveBullets(Bullets *bullets, int field_min_y, int field_max_y){

    for(int i = 0; i < MAX_BULLETS; i++) {
        if (bullets->bullets[i]->active == true){

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
                bullets->bullets[i]->active = false;
            }
        }
    }
}

void destroyBullets(Bullets **bullets){
    for(int i = 0; i < MAX_BULLETS; i++){
        free((*bullets)->bullets[i]);
    }
    free((*bullets));
    *bullets = NULL;
}
