#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>
#include "settings.h"

// Definitions
#define SPRITE_IS_SOLID(a) (sprite_table[a].flags & 1)
#define SPRITE_IS_SCROLLED(a) (sprite_table[a].flags & 2)
#define SPRITE_IS_ONEBIT(a) (sprite_table[a].flags & 4)
#define SPRITE_IS_FLIP_HORIZONTAL(a) (sprite_table[a].flags & 8)
#define SET_LINE_IS_DRAW(a) line_is_draw[(a) >> 5] |= (1 << ((a)&31))

// Structures
struct Sprite {
    uint16_t address;
    int16_t x;
    int16_t y;
    int16_t previousx;
    int16_t previousy;
    uint8_t width;
    uint8_t height;
    uint16_t size;
    uint8_t zindex;
    int8_t speedx;
    int8_t speedy;
    int16_t angle;
    int8_t lives;
    int8_t collision;
    uint8_t flags;  // 8 - 4 color, 3 flip horizontal, 2 is one bit, 1 scrolled, 0 solid
    int8_t gravity;
    uint16_t oncollision;
    uint16_t onexitscreen;
};

struct Particle {
    int16_t time;
    int16_t x;
    int16_t y;
    int8_t gravity;
    int8_t speedx;
    int8_t speedy;
    int8_t color;
    int8_t size;
};

struct Emitter {
    int16_t time;
    int16_t timer;
    int16_t timeparticle;
    uint8_t count;
    int8_t gravity;
    int16_t x;
    int16_t y;
    int8_t speedx;
    int8_t speedy;
    int8_t speedx1;
    int8_t speedy1;
    int8_t color;
    int8_t size;
    int16_t width;
    int16_t height;
};

struct Tile {
    int16_t adr;
    uint8_t imgwidth;
    uint8_t imgheight;
    uint8_t width;
    uint8_t height;
    int16_t x;
    int16_t y;
    uint16_t pixwidth;
    uint16_t pixheight;
    uint16_t collisionMap;
};

struct CustomFont {
    int16_t address;
    int8_t start;
    int8_t end;
    int16_t imgwidth;
    int16_t imgheight;
    int8_t charwidth;
    int8_t charheight;
    int8_t columns;
};

// Global variables
extern uint8_t *screen;
extern uint8_t *sprite_screen;
extern uint32_t line_is_draw[4];
extern char charArray[340];
extern uint16_t pix_buffer[SCREEN_REAL_WIDTH];
extern uint16_t rscreenWidth;
extern uint16_t rscreenHeight;
extern uint16_t displayXOffset;
extern struct Sprite sprite_table[SPRITE_COUNT];
extern struct Particle particles[PARTICLE_COUNT];
extern struct Emitter emitter;
extern struct Tile tile;
extern struct CustomFont custom_font;

// Function prototypes
void screenMemoryAlloc();
void screenMemoryFree();
int16_t atan2_fp(int16_t y_fp, int16_t x_fp);
void display_init();
char pause();
void drawPause();
int randomD(int a, int b);
void setParticle(int8_t gravity, uint8_t count, uint16_t time);
void setEmitter(uint16_t time, int16_t dir, int16_t dir1, int16_t speed);
void setEmitterSize(uint8_t width, uint8_t height, uint8_t size);
void drawParticle(int16_t x, int16_t y, uint8_t color);
void setScreenResolution(uint16_t nw, uint16_t nh);
uint16_t getDisplayXOffset();
void redrawScreen();
inline void setRedrawRect(uint8_t s, uint8_t e);
inline void drawSprFHLine(int16_t x1, int16_t x2, int16_t y, int8_t c);
void largeParticle(int16_t x0, int16_t y0, int16_t r, int8_t c);
void updateEmitter();
void redrawParticles();
int16_t getSpriteInXY(int16_t x, int16_t y);
inline void moveSprites();
inline void redrawSprites();
void setTileCollisionMap(int16_t adr);
uint16_t getTileInXY(int16_t x, int16_t y, int16_t collisionMapAdr);
void resolveCollision(uint8_t n, uint8_t i);
inline void testSpriteCollision();
inline void clearSpriteScr();
void clearScr(uint8_t color);
void spriteDebug();
inline void setImageSize(uint16_t size);
inline void setSpr(uint16_t n, uint16_t adr);
void setSprPosition(uint16_t n, uint16_t x, uint16_t y);
void spriteSetDirectionAndSpeed(uint16_t n, uint16_t speed, int16_t dir);
inline void setSprWidth(uint16_t n, uint8_t w);
inline void setSprHeight(uint16_t n, uint8_t w);
inline void setSprSize(uint16_t n, uint16_t s);
inline void setSprSpeedx(uint16_t n, int8_t s);
inline void setSprSpeedy(uint16_t n, int8_t s);
int16_t angleBetweenSprites(uint16_t n1, int8_t n2);
int16_t getSpriteValue(uint16_t n, uint16_t t);
void setSpriteValue(uint16_t n, uint16_t t, int16_t v);
inline void drawRotateSprPixel(int8_t pixel, int16_t x0, int16_t y0, int16_t x, int16_t y, int16_t hw, int16_t hh, int16_t c, int16_t s);
inline void drawSprPixel(int8_t pixel, int16_t x0, int16_t y0, int16_t x, int16_t y);
void drawSpr(int16_t n, int16_t x, int16_t y);
void drawImg(int16_t a, int16_t x, int16_t y, int16_t w, int16_t h);
void drawImgRLE(int16_t adr, int16_t x1, int16_t y1, int16_t w, int16_t h);
void drawImageBit(int16_t adr, int16_t x1, int16_t y1, int16_t w, int16_t h);
void drawImgS(int16_t a, int16_t x, int16_t y, int32_t w, int32_t h);
void drawImgRLES(int16_t adr, int16_t x1, int16_t y1, int16_t w, int16_t h);
void drawImageBitS(int16_t a, int16_t x, int16_t y, int16_t w, int16_t h);
void loadTile(int16_t adr, uint8_t iwidth, uint8_t iheight, uint8_t width, uint8_t height);
void drawTile(int16_t x0, int16_t y0);
inline void drawFVLine(int x, int y1, int y2);
void drawFHLine(int16_t x1, int16_t x2, uint16_t y);
void drwLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void setClip(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
inline void setPix(uint16_t x, uint16_t y, uint8_t c);
uint8_t getPix(uint8_t x, uint8_t y);
void changePalette(uint8_t n, uint16_t c);
void scrollScreen(uint8_t step, uint8_t direction);
void tileDrawLine(uint8_t step, uint8_t direction);
void charLineUp(uint8_t n);
inline void setCharX(int8_t x);
inline void setCharY(int8_t y);
inline int8_t getCharY();
void printc(char c, uint8_t fc, uint8_t bc);
void printfix(int16_t value, uint8_t fc, uint8_t bc);
inline void setColor(uint8_t c);
inline void setBgColor(uint8_t c);
void drwRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void fillRect(int8_t x, int8_t y, uint8_t w, uint8_t h, uint8_t c);
void fllRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void drwCirc(int16_t x0, int16_t y0, int16_t r);
void fllCirc(int16_t x0, int16_t y0, int16_t r);
void drwTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);
void fllTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void putString(char s[], int8_t y) ;
void putchar(char c, uint8_t x, uint8_t y);
void drawChar(uint8_t c, uint16_t x, uint16_t y);
void drawString(uint16_t s, uint16_t x, uint16_t y);
void fontload(int16_t adr, int8_t start, int8_t end) ;
void fontsize(int16_t imgwidth, int16_t imgheight, int16_t charwidth, int16_t charheight);
#endif // DISPLAY_HPP