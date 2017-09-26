#include <assert.h>
#include "../include/bullets.h"
#include "../include/ship.h"
#include "../include/aliens.h"
#include "../include/c_window.h"
#include "../include/main.h"

/* void resizeHandler(int sig){ */
/*     int nh, nw; */
/*     getmaxyx(stdscr, nh, nw); */
/* } */

int level_difficulty = 50;

// Check for collisions.
void checkAlienCollisions(Bullets *bullets, Aliens *aliens, int *const score){

    // Only check if they are the correct 'height'
    for(int i = 0; i < MAX_ALIENS; i++){
        if(aliens->aliens[i]->dead != TRUE){
            for(int j = 0; j < MAX_BULLETS; j++){
                if(bullets->bullets[j]->active == TRUE && bullets->bullets[j]->type == SHIP){
                    if(aliens->aliens[i]->curr_y == bullets->bullets[j]->curr_y &&
                       aliens->aliens[i]->curr_x == bullets->bullets[j]->curr_x){
                        // hit alien.
                        bullets->bullets[j]->active = FALSE;
                        killAlien(aliens->aliens[i], score);
                        aliens->aliensRemaining--;
                        break;
                    }
                }
            }
        }
    }
}

void checkShipCollision(Bullets *bullets, Ship *ship){
    for(int i = 0; i < MAX_BULLETS; i++){
        if(bullets->bullets[i]->type == ALIEN && bullets->bullets[i]->curr_y == ship->posY &&
                bullets->bullets[i]->curr_x == ship->posX){
            ship->health -= 25;
            // Probably not needed.
            // But from a single cycle, only a single bullet at hit the ship at any time.
            // Once detected, wasting loop.
            break;
        }
    }
}

void closeProgram(Ship* ship, Aliens *aliens, Bullets *bullets){
    destroyAliens(&aliens);
    destroyShip(ship);
    destroyBullets(bullets);
    endwin();
}

int main() {

    /* signal(SIGWINCH, resizeHandler); */
//    pthread_t gui_thread;       // Need all GUI calls to come from this thread.
//    pthread_t movement_thread;

//    if(pthread_create(&gui_thread, NULL, guiFunction, NULL)){
//        exit(EXIT_FAILURE);
//    }
//
//    pthread_join(gui_thread, NULL);

    srand((unsigned int) time(NULL));

    WINDOW *win_field = NULL;
    WINDOW *win_score = NULL;
    WINDOW *win_banner = NULL;
    WINDOW *win_level = NULL;
    WINDOW *win_health = NULL;

    int max_x = 0;
    int max_y = 0;
    int field_max_x = 0;
    int field_max_y = 0;

//    int tmpInt = get_escdelay();
//    int successful;
//    // Attempt to reduce escape delay.
//    // Holding down particular key should not wait the default 1000ms.
//    successful = set_escdelay(0);
//    tmpInt = get_escdelay();

//    int health_int = 0;
//    int *const health = &health_int;

    int score_int = 0;
    int *const score = &score_int;

    int level_int = 1;
    int *const level = &level_int;

    initscr();          // Initialising screen.
    noecho();           // Stops character being displayed on screen.
    cbreak();           // Does not wait for line break.
    curs_set(FALSE);    // Disables cursor.
//    int tmpInt = get_escdelay();
//    int successful = set_escdelay(0);
//    tmpInt = get_escdelay();

    getmaxyx(stdscr, max_y, max_x);
    // Main window
    win_field = setupWindow(max_y - 3, max_x, 3, 0);

    // Top three windows.
    win_banner = setupWindow(3, max_x / 4, 0, 0);
    win_level = setupWindow(3, max_x / 4 + 1, 0, max_x / 4);
    win_health = setupWindow(3, max_x / 4 + 1, 0, 2* max_x / 4);
    win_score = setupWindow(3, max_x / 4, 0, 3* max_x / 4 + 1);

    getmaxyx(win_field, field_max_y, field_max_x);

    Ship *ship = setupShip(100, field_max_x, field_max_y - 1);
    Aliens *aliens = setupAliens(MAX_ALIENS);
    Bullets *bullets = setupBullets();

    int ch;             // User entered character.
    keypad(win_field, TRUE);   // Enables keypad.
    nodelay(win_field, TRUE);

    wclear(win_banner);
    displayBanner(win_banner);
    drawBorders(win_banner);
    wrefresh(win_banner);

//    closeProgram(ship, aliens, bullets);

    for (;;) {
        ////////////// NEED TO BE SLOWER.
        wclear(win_field);

        wclear(win_health);
        wclear(win_score);
        wclear(win_level);

        // FIXME: can be on separate thread.
        moveAliens(aliens, bullets, 0, field_max_x, field_max_y, level_difficulty);

        displayScore(win_score, score);
        displayLevel(win_level, level);
        displayHealth(win_health, ship);

        displayAliens(win_field, aliens);
        displayBullets(win_field, bullets);
        mvwprintw(win_field, ship->posY, ship->posX, &ship->body);

        drawBorders(win_field);
        drawBorders(win_health);
        drawBorders(win_score);
        drawBorders(win_level);

        wrefresh(win_field);
        wrefresh(win_health);
        wrefresh(win_score);
        wrefresh(win_level);

        moveBullets(bullets, 0, field_max_y);
        checkAlienCollisions(bullets, aliens, score);
        checkShipCollision(bullets, ship);

        usleep(DELAY);
        ////////////////
//        }

//         Lose condition when the alien row hit the same row as the ship.
        if (ship->health <= 0 || aliens->aliensWin == TRUE) {
            wclear(win_field);
            char *LOSE_MESSAGE = "YOU LOSE";
            mvwprintw(win_field, field_max_y/2, field_max_x/2 - 2, LOSE_MESSAGE);
            drawBorders(win_field);
            wrefresh(win_field);
            sleep(MESSAGE_DELAY);
            closeProgram(ship, aliens, bullets);
            return 0;
        }

        if (aliens->aliensRemaining == 0){
            wclear(win_field);
            char *LOSE_MESSAGE = "YOU WIN";
            mvwprintw(win_field, field_max_y/2, field_max_x/2 - 2, LOSE_MESSAGE);
            drawBorders(win_field);
            wrefresh(win_field);
            sleep(MESSAGE_DELAY);
            closeProgram(ship, aliens, bullets);
            return 0;
        }

        if ((ch = wgetch(win_field)) != ERR) {
            // Flushes user input. Prevents input being queued.
//            tmpInt = get_escdelay();
            flushinp();
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
                    shoot(bullets, ship->posY, ship->posX, SHIP);
                    break;

                case KEY_DOWN:      // Exit condition.
                    closeProgram(ship, aliens, bullets);
//                    destroyShip(ship);
//                    assert(ship == NULL);
//                    destroyAliens(aliens);
//                    assert(ship == NULL);
                    return 0;
            }
        }
    }
}


//void *guiFunction(void *ptr){
//
//    srand((unsigned int) time(NULL));
//
//    WINDOW *win_field;
//    WINDOW *win_score;
//    WINDOW *win_banner;
//    WINDOW *win_level;
//
//    int max_x = 0;
//    int max_y = 0;
//    int field_max_x = 0;
//    int field_max_y = 0;
//
//    int score_int = 0;
//    int *const score = &score_int;
//
//    int level_int = 1;
//    int *const level = &level_int;
//
//    initscr();          // Initialising screen.
//    noecho();           // Stops character being displayed on screen.
//    cbreak();           // Does not wait for line break.
//    curs_set(FALSE);    // Disables cursor.
//
//    getmaxyx(stdscr, max_y, max_x);
//    // Main window
//    win_field = setupWindow(max_y - 3, max_x, 3, 0);
//
//    // Top three windows.
//    win_level = setupWindow(3, max_x / 3, 0, 0);
//    win_banner = setupWindow(3, max_x / 3 + 1, 0, max_x / 3);
//    win_score = setupWindow(3, max_x / 3, 0, 2* max_x / 3 + 1);
//
//    getmaxyx(win_field, field_max_y, field_max_x);
//
//    Ship *ship = setupShip(100, field_max_x, field_max_y - 1);
//    struct Aliens *aliens = setupAliens(MAX_ALIENS);
//    struct Bullets *bullets = setupBullets();
//
//    int ch;             // User entered character.
//    keypad(win_field, TRUE);   // Enables keypad.
//    nodelay(win_field, TRUE);
//
//    wclear(win_banner);
//    displayBanner(win_banner);
//    drawBorders(win_banner);
//    wrefresh(win_banner);
//
//    for (;;) {
//        ////////////// NEED TO BE SLOWER.
//        wclear(win_field);
//        wclear(win_score);
//        wclear(win_level);
//
//        // FIXME: can be on separate thread.
//        moveAliens(aliens, 0, field_max_x, field_max_y);
//
//        displayScore(win_score, score);
//        displayLevel(win_level, level);
//
//        displayAliens(win_field, aliens);
//        displayBullets(win_field, bullets);
//        mvwprintw(win_field, ship->posY, ship->posX, &ship->body);
//
//        drawBorders(win_field);
//        drawBorders(win_score);
//        drawBorders(win_level);
//
//        wrefresh(win_field);
//        wrefresh(win_score);
//        wrefresh(win_level);
//
//        moveBullets(bullets, 0);
//        checkAlienCollisions(bullets, aliens, score);
//
//        usleep(DELAY);
//        ////////////////
////        }
//
////         Lose condition when the alien row hit the same row as the ship.
//        if (aliens->aliensWin == TRUE) {
//            wclear(win_field);
//            char *LOSE_MESSAGE = "YOU LOSE";
//            mvwprintw(win_field, field_max_y/2, field_max_x/2 - 2, LOSE_MESSAGE);
//            drawBorders(win_field);
//            wrefresh(win_field);
//            sleep(MESSAGE_DELAY);
//            endwin();
//            return 0;
//        }
//
//        if (aliens->aliensRemaining == 0){
//            wclear(win_field);
//            char *LOSE_MESSAGE = "YOU WIN";
//            mvwprintw(win_field, field_max_y/2, field_max_x/2 - 2, LOSE_MESSAGE);
//            drawBorders(win_field);
//            wrefresh(win_field);
//            sleep(MESSAGE_DELAY);
//            endwin();
//            return 0;
//        }
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
//                    shoot(bullets, ship->posY, ship->posX);
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
//}
