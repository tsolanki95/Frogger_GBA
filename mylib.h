#ifndef LIB
#define LIB
#define OFFSET(r,c) ((r)*240+(c))
#define OFFSETF(r, c, rowlen)  ((r)*(rowlen)+(c))
typedef unsigned short u16;
typedef unsigned char uChar;
typedef unsigned int uInt;

#define REG_DISPCTL *(u16 *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define RGB(r,g,b) ((r) | (g) << 5 | (b) << 10)
#define RED RGB(31,0,0)
#define GREEN RGB(0,31,0)
#define BLUE RGB(0,0,31)
#define CYAN RGB(0,31,31)
#define YELLOW RGB(31,31,0)
#define WHITE RGB(31,31,31)
#define MAGENTA RGB(31,0,31)
#define BROWN RGB(26,23,18)
#define BLACK 0

#define BUTTON_ADDRESS *(volatile unsigned short*) 0x4000130
#define BUTTON_DOWN_NOW(key) (~BUTTON_ADDRESS & (key))
#define SCANLINECOUNTER *(volatile unsigned short*) 0x4000006

#define BUTTON_A 1
#define BUTTON_B (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START (1<<3)
#define BUTTON_RIGHT (1<<4)
#define BUTTON_LEFT (1<<5)
#define BUTTON_UP (1<<6)
#define BUTTON_DOWN (1<<7)
#define BUTTON_R (1<<8)
#define BUTTON_L (1<<9)
#define NELEMS(x)  (sizeof(x) / sizeof(x[0])) 

const unsigned char fontdata_6x8[12288];
#endif

void incrementFrogUp();

void incrementFrogDown();

void incrementFrogLeft();

void incrementFrogRight();

u16 *videoBuffer;

// A function to set pixel (r,c) to the color passed in
void setPixel(int r, int c, u16 color);

// A function to draw a FILLED rectangle starting at (r,c)
void drawRect(int r, int c, int width, int height, u16 color);

// A function to draw a HOLLOW rectangle starting at (r,c)
void drawHollowRect(int r, int c, int width, int height, u16 color);

// A function to plot a line from (x0,y0) to (x1,y1)
void plotLine(int x0, int y0, int x1, int y1, u16 color);

void waitForVBlank();

void displayTitleScreen();

void displayWinScreen();

void displayLoseScreen();

void drawBackground();

void drawFrog();

void init();

void drawLog();

void incrementLog();

int isOnLog();

int isInWater();

int isOnLily();

int isOnLilyWater();

void drawCar();

void incrementCar();

int isHitByCar();

void decrementLives();

int isDead();

void resetLives();

u16 getPixel(int x, int y);