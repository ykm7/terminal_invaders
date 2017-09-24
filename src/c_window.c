//
// Created by yoakim on 24/09/17.
//

#include "../include/c_window.h"

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

void displayHealth(WINDOW *win, struct Ship *ship){
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

void destroyWin(WINDOW *win){
    free(win);
}
