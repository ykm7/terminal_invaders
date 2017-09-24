#include "main.h"

/* void resizeHandler(int sig){ */
/*     int nh, nw; */
/*     getmaxyx(stdscr, nh, nw); */
/* } */

int level_difficulty = 1;

//struct Aliens* setupAliens(const int numAliens) {
//
//    struct Aliens* aliens = (struct Aliens *)malloc(sizeof(struct Aliens));
//    aliens->totalNumAliens = numAliens;
//    aliens->aliensRemaining = numAliens;
//    aliens->aliensWin = FALSE;
//    for(int i = 0; i < numAliens; i++){
//        aliens->aliens[i] = (struct Alien*)malloc(sizeof(struct Alien) * numAliens);
//        aliens->aliens[i]->body = 'X';
//        aliens->aliens[i]->curr_x = i + 1;
//        aliens->aliens[i]->curr_y = 1;
//        aliens->aliens[i]->direction = 1;
//        aliens->aliens[i]->value = 25;
//        aliens->aliens[i]->dead = FALSE;
//    }
//    return aliens;
//}

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
}

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

//void destroyAliens(struct Aliens *aliens){
//   for(int i = 0; i < aliens->totalNumAliens; i++){
//       free(aliens->aliens[i]);
//   }
//    free(aliens->aliens);
//    free(aliens);
//}
//
///**
// * Returns 1 when the aliens reach the bottom layer.
// * @param aliens
// * @param win_field
// * @param curr_y_pos
// * @param curr_x_pos
// * @return
// */
//void moveAliens(struct Aliens *aliens, int field_start_x, int field_end_x, int field_end_y){
//    for(int i = 0; i < aliens->totalNumAliens; i++){
////        if(aliens->aliens[i] != NULL){
//        if(aliens->aliens[i]->dead != TRUE){
//
////            // Do not move alien if dead.
////            if(aliens->aliens[i]->dead == TRUE){
////                continue;
////            }
//
//            aliens->aliens[i]->curr_x += aliens->aliens[i]->direction;
//
//            if(aliens->aliens[i]->curr_x <= field_start_x ||
//               aliens->aliens[i]->curr_x >= field_end_x){
//                aliens->aliens[i]->curr_y++;
//                aliens->aliens[i]->direction *= -1;
//            }
//
//            // Aliens shooting should increase as the levels progress.
//            if((rand() % MAX_ALIENS) >= level_difficulty * 5){
//
//            }
//
//            // Checking when aliens hit the floor.
//            if(aliens->aliens[i]->curr_y >= field_end_y - 2){
//                aliens->aliensWin = TRUE;
//                break;
//            }
//        }
//    }
//}
//
//void displayAliens(WINDOW *win_field, struct Aliens *aliens){
//    for(int i = 0; i < aliens->totalNumAliens; i++) {
//            mvwprintw(win_field, aliens->aliens[i]->curr_y, aliens->aliens[i]->curr_x, &(aliens->aliens[i]->body));
//    }
//}

//:X

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

void destroyBullets(struct Bullets *bullets){
    for(int i = 0; i < MAX_BULLETS; i++){
        free(bullets->bullets[i]);
    }
    free(bullets);
}

void shoot(struct Bullets *bullets, int pos_y, int pos_x){

    bullets->bullets[bullets->current]->active = TRUE;
    bullets->bullets[bullets->current]->curr_x = pos_x;
    bullets->bullets[bullets->current]->curr_y = pos_y;
    bullets->bullets[bullets->current]->body = 'o';
    bullets->current++;
    if(bullets->current == MAX_BULLETS){
        bullets->current = 0;
    }
}

/**
 * Move bullets up by one.
 * @param bullets
 */
void moveBullets(struct Bullets *bullets, int field_min_y){

    for(int i = 0; i < MAX_BULLETS; i++) {
        if (bullets->bullets[i]->active == TRUE)
            bullets->bullets[i]->curr_y--;

        if (bullets->bullets[i]->curr_y == field_min_y) {
            bullets->bullets[i]->active = FALSE;
        }
    }
}

void displayBullets(WINDOW* win, struct Bullets *bullets){
    for(int i = 0; i < MAX_BULLETS; i++){
        if(bullets->bullets[i]->active == TRUE){
            mvwprintw(win, bullets->bullets[i]->curr_y, bullets->bullets[i]->curr_x, &(bullets->bullets[i]->body));
        }
    }
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

void killAlien(struct Alien *alien, int *const score){
    alien->dead = TRUE;
    alien->direction = 0;
    alien->body = ' ';
    (*score) += alien->value;
}

// Check for collisions.
void checkCollisions(struct Bullets *bullets, struct Aliens *aliens, int *const score){

    // Only check if they are the correct 'height'
    for(int i = 0; i < MAX_ALIENS; i++){
        if(aliens->aliens[i]->dead != TRUE){
            for(int j = 0; j < MAX_BULLETS; j++){
                if(bullets->bullets[j]->active == TRUE){
                    if(aliens->aliens[i]->curr_y == bullets->bullets[j]->curr_y &&
                       aliens->aliens[i]->curr_x == bullets->bullets[j]->curr_x){
                        // HIT!!
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

void *guiFunction(void *ptr){

    srand((unsigned int) time(NULL));

    WINDOW *win_field;
    WINDOW *win_score;
    WINDOW *win_banner;
    WINDOW *win_level;

    int max_x = 0;
    int max_y = 0;
    int field_max_x = 0;
    int field_max_y = 0;

    int score_int = 0;
    int *const score = &score_int;

    int level_int = 1;
    int *const level = &level_int;

//    int time_int = 0;
//    int *const time = &time_int;

//    int curr_alien_x = 0;


    initscr();          // Initialising screen.
    noecho();           // Stops character being displayed on screen.
    cbreak();           // Does not wait for line break.
    curs_set(FALSE);    // Disables cursor.

    getmaxyx(stdscr, max_y, max_x);
    // Main window
    win_field = setupWindow(max_y - 3, max_x, 3, 0);

    // Top three windows.
    win_level = setupWindow(3, max_x / 3, 0, 0);
    win_banner = setupWindow(3, max_x / 3 + 1, 0, max_x / 3);
    win_score = setupWindow(3, max_x / 3, 0, 2* max_x / 3 + 1);

    getmaxyx(win_field, field_max_y, field_max_x);

    struct Ship *ship = setupShip(100, field_max_x, field_max_y - 1);
    struct Aliens *aliens = setupAliens(MAX_ALIENS);
    struct Bullets *bullets = setupBullets();

    int ch;             // User entered character.
    keypad(win_field, TRUE);   // Enables keypad.
    nodelay(win_field, TRUE);

    int tmpSingleUse = 0;

    wclear(win_banner);
    displayBanner(win_banner);
    drawBorders(win_banner);
    wrefresh(win_banner);

    for (;;) {
        ////////////// NEED TO BE SLOWER.
        wclear(win_field);
        wclear(win_score);
        wclear(win_level);

        // FIXME: can be on separate thread.
        moveAliens(aliens, 0, field_max_x, field_max_y);

        displayScore(win_score, score);
        displayLevel(win_level, level);

        displayAliens(win_field, aliens);
        displayBullets(win_field, bullets);
        mvwprintw(win_field, ship->posY, ship->posX, &ship->body);

        drawBorders(win_field);
        drawBorders(win_score);
        drawBorders(win_level);

        wrefresh(win_field);
        wrefresh(win_score);
        wrefresh(win_level);

//        curr_alien_x += 1;

        moveBullets(bullets, 0);
        checkCollisions(bullets, aliens, score);

        usleep(DELAY);
        ////////////////
//        }

//         Lose condition when the alien row hit the same row as the ship.
        if (aliens->aliensWin == TRUE) {
            wclear(win_field);
            char *LOSE_MESSAGE = "YOU LOSE";
            mvwprintw(win_field, field_max_y/2, field_max_x/2 - 2, LOSE_MESSAGE);
            drawBorders(win_field);
            wrefresh(win_field);
            sleep(MESSAGE_DELAY);
            endwin();
            return 0;
        }

        if (aliens->aliensRemaining == 0){
            wclear(win_field);
            char *LOSE_MESSAGE = "YOU WIN";
            mvwprintw(win_field, field_max_y/2, field_max_x/2 - 2, LOSE_MESSAGE);
            drawBorders(win_field);
            wrefresh(win_field);
            sleep(MESSAGE_DELAY);
            endwin();
            return 0;
        }

        if(tmpSingleUse < 3){
            tmpSingleUse++;
            shoot(bullets, ship->posY, ship->posX);
        }

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
                    shoot(bullets, ship->posY, ship->posX);
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
//    pthread_t movement_thread;

    if(pthread_create(&gui_thread, NULL, guiFunction, NULL)){
        exit(EXIT_FAILURE);
    }

    pthread_join(gui_thread, NULL);
}
