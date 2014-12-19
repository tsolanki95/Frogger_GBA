#include "mylib.h"
#include <stdlib.h>

// 240x160 display
int main(void) {
    /* Setup */
    REG_DISPCTL = MODE3 | BG2_ENABLE;
    waitForVBlank();
	int state = 0;

    /* Run Game Loop */
    while(1) {

        /* Title Screen */
        displayTitleScreen();
        while(state == 0) {
            if(BUTTON_DOWN_NOW(BUTTON_SELECT)) {
                state = 1; //move to game screen
            }
            waitForVBlank();
        }

        drawBackground();
        init();
        drawLog();
        drawFrog();
        drawCar();
        while(state == 1) {
            incrementLog();
            incrementCar();
            if(BUTTON_DOWN_NOW(BUTTON_DOWN)) {
                incrementFrogDown();
            }
            else if(BUTTON_DOWN_NOW(BUTTON_UP)) {
                incrementFrogUp();
            }
            else if(BUTTON_DOWN_NOW(BUTTON_LEFT)) {
                incrementFrogLeft();
            }
            else if(BUTTON_DOWN_NOW(BUTTON_RIGHT)) {
                incrementFrogRight();
            }
            if(isInWater()) {
                if(isOnLog()) {
                    incrementFrogRight();
                } else {
                    decrementLives();
                    drawBackground();
                    init();
                    drawLog();
                    drawFrog();
                    drawCar();
                }
            }

            if (isOnLily()) {
                state = 2;
            }

            if (isOnLilyWater() || isHitByCar()) {
                decrementLives();
                drawBackground();
                init();
                drawLog();
                drawFrog();
                drawCar();
            }

            if(isDead()) {
                state = 3;
            }
            
            waitForVBlank();

        }
        if (state == 2) {
            displayWinScreen();
        }
        /* Win Screen */
        while(state == 2) {
            if(BUTTON_DOWN_NOW(BUTTON_SELECT)) {
                resetLives();
                state = 0; //move to title
            }
            waitForVBlank();
        }

        /* Lose Screen */
        if (state == 3) {
            displayLoseScreen();
        }
        while(state == 3) {
            if(BUTTON_DOWN_NOW(BUTTON_SELECT)) {
                resetLives();
                state = 0; //move to title
            }
            waitForVBlank();
        }
    }

    return 0;
}