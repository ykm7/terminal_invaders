//
// Created by yoakim on 24/09/17.
//

#include "../include/c_window.h"
#include "../include/main.h"

WINDOW *setupWindow(int height, int width, int starty, int startx){
    WINDOW *new_win;
    new_win = newwin(height, width, starty, startx);
    drawBorders(new_win);
    wrefresh(new_win);

    return new_win;
}

void drawBorders(WINDOW *win){
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
}

void displayHealth(WINDOW *win, Ship *ship){
    mvwprintw(win, 1, 1, "HEALTH: %d", ship->health);
}

void displayScore(WINDOW *win, int const *const score){
    mvwprintw(win, 1, 1, "SCORE: %d", *score);
}

void displayBanner(WINDOW *win){
    mvwprintw(win, 1, 1, "TERMINAL INVADERS");
}

void displayLevel(WINDOW *win, int const *const level){
    mvwprintw(win, 1, 1, "Level: %d", *level);
}

void displayBullets(WINDOW* win, Bullets *bullets){
    for(int i = 0; i < MAX_BULLETS; i++){
        if(bullets->bullets[i]->active == TRUE){
            mvwprintw(win, bullets->bullets[i]->curr_y, bullets->bullets[i]->curr_x, &(bullets->bullets[i]->body));
        }
    }
}

void displayAliens(WINDOW *win_field, Aliens *aliens){
    for(int i = 0; i < aliens->totalNumAliens; i++) {
        mvwprintw(win_field, aliens->aliens[i]->curr_y, aliens->aliens[i]->curr_x, &(aliens->aliens[i]->body));
    }
}

void displayHelp(WINDOW *win, int field_max_y){
    char ch;
    wclear(win);
    int y_pos = field_max_y / 4;
    while((ch = wgetch(win)) != 'q'){
        mvwprintw(win, y_pos, 5, "HELP");
        mvwprintw(win, y_pos + 1, 5, "---------------------------------");
        mvwprintw(win, y_pos + 2, 5, "Please shoot down all the aliens");
        mvwprintw(win, y_pos + 3, 5, "Arrow keys move the ship.");
        mvwprintw(win, y_pos + 4, 5, "Up causes the ship to shoot.");
        mvwprintw(win, y_pos + 5, 5, "Down or q will quit the game.");
        mvwprintw(win, y_pos + 6, 5, "---------------------------------");
        mvwprintw(win, y_pos + 7, 5, "'q' to close this help menu.");
        mvwprintw(win, y_pos + 8, 5, "---------------------------------");
        usleep(DELAY);
    }
}


