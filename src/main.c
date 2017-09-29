#include "../include/bullets.h"
#include "../include/ship.h"
#include "../include/aliens.h"
#include "../include/c_window.h"
#include "../include/main.h"

void checkAlienCollisions(Bullets *bullets, Aliens *aliens, int *const score){

    for(int i = 0; i < MAX_ALIENS; i++){
        if(aliens->aliens[i]->dead != TRUE){
            for(int j = 0; j < MAX_BULLETS; j++){
                if(bullets->bullets[j]->active == TRUE && bullets->bullets[j]->type == SHIP){
                    if(aliens->aliens[i]->curr_y == bullets->bullets[j]->curr_y &&
                       aliens->aliens[i]->curr_x == bullets->bullets[j]->curr_x){
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

void setLevel(Aliens *aliens, Bullets *bullets, int *level){

    *level += 1;            // Increases the frequency that aliens shoot.
    setupAliens(aliens);    // Restore aliens to original position.
    setupBullets(bullets);  // Reset bullets.

}

void closeProgram(Ship* ship, Aliens *aliens, Bullets *bullets){
    destroyAliens(&aliens);
    destroyShip(&ship);
    destroyBullets(&bullets);
}

int main() {

    // Used to determine what aliens shoot when.
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

    int score_int = 0;
    int *const score = &score_int;

    int level_int = 1;
    int *const level = &level_int;

    initscr();          // Initialising screen.
    noecho();           // Stops character being displayed on screen.
    cbreak();           // Does not wait for line break.
    curs_set(false);    // Disables cursor.

    getmaxyx(stdscr, max_y, max_x);
    // Main window
    win_field = setupWindow(max_y - 3, max_x, 3, 0);

    // Top three windows.
    win_banner = setupWindow(3, max_x / 4, 0, 0);
    win_level = setupWindow(3, max_x / 4 + 1, 0, max_x / 4);
    win_health = setupWindow(3, max_x / 4 + 1, 0, 2* max_x / 4);
    win_score = setupWindow(3, max_x / 4, 0, 3* max_x / 4 + 1);

    getmaxyx(win_field, field_max_y, field_max_x);

    Ship *ship = initialiseShip(100, field_max_x, field_max_y - 1);
    Aliens *aliens = initialiseAliens(MAX_ALIENS);
    Bullets *bullets = initialisingBullets();

    int ch;                         // User entered character.
    keypad(win_field, true);        // Enables keypad.
    nodelay(win_field, true);       // Causes getch to be a non-blocking function.
    notimeout(win_field, true);

    // The game banner should change.
    wclear(win_banner);
    displayBanner(win_banner);
    drawBorders(win_banner);
    wrefresh(win_banner);

    for (;;) {
        ////////////// NEED TO BE SLOWER.
        wclear(win_field);
        wclear(win_health);
        wclear(win_score);
        wclear(win_level);

        moveAliens(aliens, bullets, 0, field_max_x, field_max_y, level);

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
            mvwprintw(win_field, field_max_y/2, field_max_x/2 - 1, LOSE_MESSAGE);
            drawBorders(win_field);
            wrefresh(win_field);
            sleep(MESSAGE_DELAY);
            closeProgram(ship, aliens, bullets);
            endwin();
            return 0;
        }

        // Win condition.
        if (aliens->aliensRemaining == 0){
            setLevel(aliens, bullets, level);
            wclear(win_field);
            mvwprintw(win_field, field_max_y/2, field_max_x/2 - 7, "LEVEL COMPLETE");
            drawBorders(win_field);
            wrefresh(win_field);
            sleep(MESSAGE_DELAY / 2);
            mvwprintw(win_field, field_max_y/2, field_max_x/2 - 7, "Next Level:  %d", (*level));
            drawBorders(win_field);
            wrefresh(win_field);
            sleep(MESSAGE_DELAY / 2);
        }

        if ((ch = wgetch(win_field)) != ERR) {
            flushinp();     // Flushes user input. Prevents input being queued.
            switch (ch) {
                case 'h':
                    displayHelp(win_field, field_max_y);
//                    }
                    break;

                case KEY_LEFT:
                case 'a':
                    if (ship->posX > 1) {
                        ship->posX--;
                    }
                    break;

                case KEY_RIGHT:
                case 'd':
                    if (ship->posX < field_max_x - 2) {
                        ship->posX++;
                    }
                    break;

                case KEY_UP:        // Shooting.
                case 'w':
                    shoot(bullets, ship->posY, ship->posX, SHIP);
                    break;

                case KEY_DOWN:      // Exit condition.
                case 'q':
                    closeProgram(ship, aliens, bullets);
                    endwin();
                    return 0;
            }
        }
    }
}
