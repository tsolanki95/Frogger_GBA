#include "mylib.h"
#include "text.h"
#include <stdlib.h>
u16 *videoBuffer = (u16 *) 0x6000000;
//u16 background[240*160];

const unsigned int frogPixelData[] = {
	1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,
	1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,
	1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,

	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,

	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,

	1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,
	1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,
	1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,
};

typedef struct {
	int x;
	int y;
} Obj;

/*typedef struct {
	int x;
	int y;
} Log;

typedef struct {
	int x;
	int y;
} Frog;*/

Obj frog;

Obj logs;

Obj car;

int lives = 3;



void init() {
	frog.x = 121;
	frog.y = 142;
	logs.x = 0;
	logs.y = 20;
	car.x = 100;
	car.y = 90;
}

// draws frog at location (x,y)
void drawFrog() {
	int r, c;
	for(r=0; r<18; r++)
	{
		for(c=0; c<18; c++)
		{
			if(frogPixelData[OFFSETF(c, r, 18)])
			{
				setPixel(frog.y+c, frog.x+r, GREEN);
			}
		}
	}
}

void drawLog() {
	drawRect(logs.y,logs.x,50,30,BROWN);
}

void drawCar() {
	drawRect(car.y,car.x,50,30,RED);
}

int isInWater() {
	if (frog.y < 50 && frog.y > 20) {
		return 1;
	}
	return 0;
}

int isOnLog() {
	if (frog.y > 20 && frog.y < 50) {
		if (frog.x > logs.x && frog.x < logs.x + (50 - 18)) {
			return 1;
		}
	}
	return 0;
}

int isHitByCar() {
	if (frog.y < 120 && frog.y > 72) {
		if (frog.x > car.x && frog.x < car.x + 50) {
			return 1;
		}
	}
	return 0;
}

void incrementLog() {
	logs.x++;
	if(logs.x>=240) {
		logs.x = logs.x % 240;
	}
	
	drawRect(logs.y,logs.x - 1, 1, 30, BLUE);
	drawRect(logs.y,logs.x+50 ,1, 30, BROWN);
}

void incrementCar() {
	car.x++;
	if(car.x>=240) {
		car.x = car.x % 240;
	}

	drawRect(car.y,car.x - 1, 1, 30, BLACK);
	drawRect(car.y,car.x+50 ,1, 30, RED);
}

void undrawFrog() {
	u16 color;
	for(int i = 0; i < 18; i++) {
		color = getPixel(frog.x-1,frog.y+i);
		for (int j = 0; j < 18; j++) {
			setPixel(frog.y + i, frog.x + j, color);
		}
	}
}

void incrementFrogLeft() {
	if (frog.x > 0) {
		undrawFrog();
		frog.x--;
		drawFrog();
	}
}

int isOnLily() {
	if (frog.y < 20) {
		if ((frog.x > 22 && frog.x < 60) || (frog.x > 92 && frog.x < 130) || (frog.x > 162 && frog.x < 200)) {
			return 1;
		}
	}
	return 0;
}

int isOnLilyWater() {
	if (frog.y < 20) {
		if (!((frog.x > 22 && frog.x < 60) || (frog.x > 92 && frog.x < 130) || (frog.x > 162 && frog.x < 200))) {
			return 1;
		}
	}
	return 0;
}

void resetLives() {
	lives = 3;
}

void incrementFrogRight() {
	if (frog.x + 18 < 240) {
		undrawFrog();
		frog.x++;
		drawFrog();
	}
}

void incrementFrogDown() {
	if (frog.y < 160 - 18) {
		undrawFrog();
		frog.y++;
		drawFrog();
	}
}

void incrementFrogUp() {
	if (frog.y > 0) {
		undrawFrog();
		frog.y--;
		drawFrog();
	}
}

int isDead() {
	if (lives == 0) {
		return 1;
	} return 0;
}

void decrementLives() {
	lives--;
}

void drawText() {
	if (lives == 3) {
		drawRect(150,0,50,10,YELLOW);
		drawString(150,0,"lives: 3",CYAN);
	}
	if (lives == 2) {
		drawRect(150,0,50,10,YELLOW);
		drawString(150,0,"lives: 2",CYAN);
	}
	if (lives == 1) {
		drawRect(150,0,50,10,YELLOW);
		drawString(150,0,"lives: 1",CYAN);
	}
}

void drawBackground() {
	drawRect(0,0,240,50,BLUE); //Draw Water
	drawRect(50,0,240,30,YELLOW); //Draw Land
	drawRect(80,0,240,50,BLACK); //Draw Road
	drawRect(130,0,240,30,YELLOW); //Draw Land
	drawRect(0,40,20,20,MAGENTA);
	drawRect(0,110,20,20,MAGENTA);
	drawRect(0,180,20,20,MAGENTA);
	drawText();
}



void displayTitleScreen() {
	drawRect(0,0,240,160,RED); //draws background
	drawString(30,80,"FROGGER",GREEN); //draws title
	drawString(40,40,"Press SELECT to start game",CYAN); //draws instruction
	drawString(50,40,"Press arrow keys to move",CYAN); //draws instruction
}

void displayWinScreen() {
	drawRect(0,0,240,160,GREEN); //draws background
	drawString(30,80,"YOU WIN",RED); //draws title
	drawString(40,40,"Press SELECT to start new game",RED); //draws instruction
}

void displayLoseScreen() {
	drawRect(0,0,240,160,RED); //draws background
	drawString(30,80,"SORRY, YOU LOSE",GREEN); //draws title
	drawString(40,40,"Press SELECT to start new game",CYAN); //draws instruction
}

void setPixel(int r, int c, u16 color) {
	*(videoBuffer + OFFSET(r % 160,c % 240)) = color;
}

u16 getPixel(int x, int y) {
	return *(videoBuffer + OFFSET(y,x));
}

void drawRect(int r, int c, int width, int height, u16 color) {
	for (int i = c; i < width+c; i++)
    {
        for (int j = r; j < height+r; j++)
        {
            setPixel(j,i,color);
        }
    }
}

void drawHollowRect(int r, int c, int width, int height, u16 color) {
    int i;
    for (i = c; i < width+c; i++)
    {
        setPixel(r,i,color);
        setPixel(r+height,i,color);
    }

    for (i = r; i < height+r; i++)
    {
        setPixel(i,c,color);
        setPixel(i,c + width,color);
    }
}

void plotLine(int x0, int y0, int x1, int y1, u16 color) {
	int dx = x1 - x0;
	int dy = y1 - y0;

	int D = (dy << 1) - dx;
	setPixel(x0,y0,color);
	int y = y0;

	int x;

	for(x = x0 + 1; x <= x1; x++) {
		if (D > 0) {
			y = y+1;
			setPixel(x,y,color);
			D = D + ((dy << 1) - (dx << 1));
		} else {
			setPixel(x,y,color);
			D = D + (dy << 1);
		}
	}
}

void waitForVBlank() {
	while(SCANLINECOUNTER>160);
	while(SCANLINECOUNTER<160);
}