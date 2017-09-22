#include "main.h"

/* void resizeHandler(int sig){ */
/*     int nh, nw; */
/*     getmaxyx(stdscr, nh, nw); */
/* } */

struct Aliens* setupAliens(const int numAliens) {

    struct Aliens* aliens = (struct Aliens *)malloc(sizeof(struct Aliens));
    aliens->totalNumAliens = numAliens;
    aliens->aliensRemaining = numAliens;
    aliens->aliens = (struct Alien**)malloc(sizeof(struct Alien*));
    for(int i = 0; i < numAliens; i++){
        aliens->aliens[i] = (struct Alien*)malloc(sizeof(struct Alien) * numAliens);
        aliens->aliens[i]->body = 'X';
    }
    return aliens;
};

/**
 * Creates a basic ship.
 */
struct Ship* setupShip(int health, int intX, int intY){
    struct Ship* ship = (struct Ship*)malloc(sizeof(struct Ship));
    ship->body = 'A';
    ship->health = health;
    ship->posX = intX / 2;
    ship->posY = intY - 1;
    return ship;
};

/* void printShipInfo(struct Ship* ship){ */
/* } */

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

void destroyWin(WINDOW *win){
    free(win);
}

void destroyShip(struct Ship* ship){
    free(ship);
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
int moveAliens(struct Aliens *aliens, WINDOW *win_field, int curr_y_pos, int curr_x_pos, int field_start_x, int field_end_x){
    for(int i = 0; i < aliens->totalNumAliens; i++){

        if (curr_x_pos < field_start_x || curr_x_pos > field_end_x) {
            curr_y_pos++;
            curr_x_pos *= -1;
        }

        mvwprintw(win_field, curr_y_pos, curr_x_pos, &(aliens->aliens[i]->body));
        curr_x_pos++;
//        if(curr_y_pos >= COLS){
//            return 1;
//        }
    }
}

//:X

void *guiFunction(void *ptr){

    WINDOW *win_field;
    WINDOW *win_top_left;
    WINDOW *win_top_right;

    int max_x = 0;
    int max_y = 0;
    int field_max_x = 0;
    int field_max_y = 0;

    int curr_alien_x = 0;
    int curr_alien_y = 0;
    int alien_direction = -1;

    const int numAliens = 1;

    initscr();          // Initialising screen.
    noecho();           // Stops character being displayed on screen.
    cbreak();           // Does not wait for line break.
    curs_set(FALSE);    // Disables cursor.

    getmaxyx(stdscr, max_y, max_x);
//    wrefresh(stdscr);
    win_field = setupWindow(max_y - 5, max_x, 5, 0);
    win_top_left = setupWindow(5, max_x / 2, 0, 0);
    win_top_right = setupWindow(5, max_x / 2, 0, max_x / 2 + 1);

    getmaxyx(win_field, field_max_y, field_max_x);

    struct Ship *ship = setupShip(100, field_max_x, field_max_y - 1);
    struct Aliens *aliens = setupAliens(numAliens);

    int ch;             // User entered character.
//    keypad(stdscr, TRUE);   // Enables keypad.
    keypad(win_field, TRUE);   // Enables keypad.
//    keypad(win_field, TRUE);   // Enables keypad.
//    keypad(win_field, TRUE);   // Enables keypad.
//    nodelay(stdscr, TRUE);
    nodelay(win_field, TRUE);


    char tmpAlien = 'X';
//    time_t start_time, end_time;
    for (;;) {

//        while(difftime(end_time, start_time) > 1){
        ////////////// NEED TO BE SLOWER.
        wclear(win_field);
        wclear(win_top_left);
        wclear(win_top_right);

        moveAliens(aliens, win_field, curr_alien_y, curr_alien_x, 0, field_max_x);
        // Lose condition.
        mvwprintw(win_field, ship->posY, ship->posX, &ship->body);

        drawBorders(win_field);
        drawBorders(win_top_left);
        drawBorders(win_top_right);

        wrefresh(win_field);
        wrefresh(win_top_left);
        wrefresh(win_top_right);

        curr_alien_x += 1;
        usleep(DELAY);
        ////////////////
//        }

        // Win condition.
//        if (aliens->aliensRemaining == 0) {
//            endwin();
//            return 0;
//        }

        if ((ch = wgetch(win_field)) != ERR) {
            // User input.
            switch (ch) {
                case KEY_LEFT:
                    if (ship->posX > 1) {
                        ship->posX--;
                    }
                    break;

                case KEY_RIGHT:
                    if (ship->posX < field_max_x - 2) {
                        ship->posX++;
                    }
                    break;

                case KEY_UP:        // Shooting.
                    /*
                     * TODO:
                     * Create object moving vertically upwards.
                     * Check if it connects to alien.
                     * If it does destroy alien and itself.
                     * Add score.
                     */
                    break;

                case KEY_DOWN:      // Exit condition.
                    destroyShip(ship);
                    destroyAliens(aliens);
                    endwin();       // Reset terminal to default.
                    return 0;
            }
        }
    }
}

int main() {

    /* signal(SIGWINCH, resizeHandler); */
    pthread_t gui_thread;       // Need all GUI calls to come from this thread.
    pthread_t movement_thread;

    if(pthread_create(&gui_thread, NULL, guiFunction, NULL)){
        exit(EXIT_FAILURE);
    }

    pthread_join(gui_thread, NULL);

//    WINDOW *win_field;
//    WINDOW *win_top_left;
//    WINDOW *win_top_right;
//
//    int max_x = 0;
//    int max_y = 0;
//    int field_max_x = 0;
//    int field_max_y = 0;
//
//    int curr_alien_x = 0;
//    int curr_alien_y = 0;
//    int alien_direction = -1;
//
//    const int numAliens = 1;
//
//    initscr();          // Initialising screen.
//    noecho();           // Stops character being displayed on screen.
//    cbreak();           // Does not wait for line break.
//    curs_set(FALSE);    // Disables cursor.
//
//    getmaxyx(stdscr, max_y, max_x);
////    wrefresh(stdscr);
//    win_field = setupWindow(max_y - 5, max_x, 5, 0);
//    win_top_left = setupWindow(5, max_x / 2, 0, 0);
//    win_top_right = setupWindow(5, max_x / 2, 0, max_x / 2 + 1);
//
//    getmaxyx(win_field, field_max_y, field_max_x);
//
//    struct Ship *ship = setupShip(100, field_max_x, field_max_y - 1);
//    struct Aliens *aliens = setupAliens(numAliens);
//
//    int ch;             // User entered character.
////    keypad(stdscr, TRUE);   // Enables keypad.
//    keypad(win_field, TRUE);   // Enables keypad.
////    keypad(win_field, TRUE);   // Enables keypad.
////    keypad(win_field, TRUE);   // Enables keypad.
////    nodelay(stdscr, TRUE);
//    nodelay(win_field, TRUE);
//
//
//    char tmpAlien = 'X';
////    time_t start_time, end_time;
//    for (;;) {
//
////        while(difftime(end_time, start_time) > 1){
//            ////////////// NEED TO BE SLOWER.
//            wclear(win_field);
//            wclear(win_top_left);
//            wclear(win_top_right);
//
//            moveAliens(aliens, win_field, curr_alien_y, curr_alien_x, 0, field_max_x);
//            // Lose condition.
//            mvwprintw(win_field, ship->posY, ship->posX, &ship->body);
//
//            drawBorders(win_field);
//            drawBorders(win_top_left);
//            drawBorders(win_top_right);
//
//            wrefresh(win_field);
//            wrefresh(win_top_left);
//            wrefresh(win_top_right);
//
//            curr_alien_x += 1;
//            usleep(DELAY);
//            ////////////////
////        }
//
//        // Win condition.
////        if (aliens->aliensRemaining == 0) {
////            endwin();
////            return 0;
////        }
//
//        if ((ch = wgetch(win_field)) != ERR) {
//            // User input.
//            switch (ch) {
//                case KEY_LEFT:
//                    if (ship->posX > 1) {
//                        ship->posX--;
//                    }
//                    break;
//
//                case KEY_RIGHT:
//                    if (ship->posX < field_max_x - 2) {
//                        ship->posX++;
//                    }
//                    break;
//
//                case KEY_UP:        // Shooting.
//                    /*
//                     * TODO:
//                     * Create object moving vertically upwards.
//                     * Check if it connects to alien.
//                     * If it does destroy alien and itself.
//                     * Add score.
//                     */
//                    break;
//
//                case KEY_DOWN:      // Exit condition.
//                    destroyShip(ship);
//                    destroyAliens(aliens);
//                    endwin();       // Reset terminal to default.
//                    return 0;
//            }
//        }
//    }
}
