#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Arduino.h>
#include "settings.h"
#include <font_a.h>
#include <sound.h>
#include <io.h>
#include <esp_lge.h>
#include <file_manager.h>
#include <lge_memory.h>
#include <cpu.h>
#include <progmem/pauseImage.h>
#include <progmem/keyboardImage.h>
#include <progmem/color_palette.h>

// Definitions
#define SPRITE_IS_SOLID(a) (sprite_table[a].flags & 1)
#define SPRITE_IS_SCROLLED(a) (sprite_table[a].flags & 2)
#define SPRITE_IS_ONEBIT(a) (sprite_table[a].flags & 4)
#define SPRITE_IS_FLIP_HORIZONTAL(a) (sprite_table[a].flags & 8)
#define SET_LINE_IS_DRAW(a) line_is_draw[(a) >> 5] |= (1 << ((a) & 31))

// Structures
struct Sprite
{
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
    uint8_t flags; // 8 - 4 color, 3 flip horizontal, 2 is one bit, 1 scrolled, 0 solid
    int8_t gravity;
    uint16_t oncollision;
    uint16_t onexitscreen;
};

struct Particle
{
    int16_t time;
    int16_t x;
    int16_t y;
    int8_t gravity;
    int8_t speedx;
    int8_t speedy;
    int8_t color;
    int8_t size;
};

struct Emitter
{
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

struct Tile
{
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

struct CustomFont
{
    int16_t address;
    int8_t start;
    int8_t end;
    int16_t imgwidth;
    int16_t imgheight;
    int8_t charwidth;
    int8_t charheight;
    int8_t columns;
};

extern uint8_t *screen __attribute__((aligned));
extern uint8_t *sprite_screen __attribute__((aligned));
extern uint32_t line_is_draw[4] __attribute__((aligned));
extern char charArray[340] __attribute__((aligned));
extern uint16_t pix_buffer[SCREEN_REAL_WIDTH] __attribute__((aligned));
extern uint16_t rscreenWidth;
extern uint16_t rscreenHeight;
extern uint16_t displayXOffset;
extern struct Sprite sprite_table[SPRITE_COUNT] __attribute__((aligned));
extern struct Particle particles[PARTICLE_COUNT] __attribute__((aligned));
extern struct Emitter emitter;
extern struct Tile tile;
extern struct CustomFont custom_font;
extern int16_t imageSize;
extern int8_t regx;
extern int8_t regy;
extern int8_t isDrawKeyboard;
extern int8_t keyboardPos;
extern uint8_t clipx0;
extern uint8_t clipx1;
extern uint8_t clipy0;
extern uint8_t clipy1;
extern uint8_t isClip;

#define SPRITE_IS_SOLID(a) (sprite_table[a].flags & 1)
#define SPRITE_IS_SCROLLED(a) (sprite_table[a].flags & 2)
#define SPRITE_IS_ONEBIT(a) (sprite_table[a].flags & 4)
#define SPRITE_IS_FLIP_HORIZONTAL(a) (sprite_table[a].flags & 8)
#define SET_LINE_IS_DRAW(a) line_is_draw[(a) >> 5] |= (1 << ((a) & 31))

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
void largeParticle(int16_t x0, int16_t y0, int16_t r, int8_t c);
void updateEmitter();
void redrawParticles();
int16_t getSpriteInXY(int16_t x, int16_t y);
void setTileCollisionMap(int16_t adr);
uint16_t getTileInXY(int16_t x, int16_t y, int16_t collisionMapAdr);
void resolveCollision(uint8_t n, uint8_t i);
void clearScr(uint8_t color);
void spriteDebug();
void setSprPosition(uint16_t n, uint16_t x, uint16_t y);
void spriteSetDirectionAndSpeed(uint16_t n, uint16_t speed, int16_t dir);
int16_t angleBetweenSprites(uint16_t n1, int8_t n2);
int16_t getSpriteValue(uint16_t n, uint16_t t);
void setSpriteValue(uint16_t n, uint16_t t, int16_t v);
void drawSpr(int16_t n, int16_t x, int16_t y);
void drawImg(int16_t a, int16_t x, int16_t y, int16_t w, int16_t h);
void drawImgRLE(int16_t adr, int16_t x1, int16_t y1, int16_t w, int16_t h);
void drawImageBit(int16_t adr, int16_t x1, int16_t y1, int16_t w, int16_t h);
void drawImgS(int16_t a, int16_t x, int16_t y, int32_t w, int32_t h);
void drawImgRLES(int16_t adr, int16_t x1, int16_t y1, int16_t w, int16_t h);
void drawImageBitS(int16_t a, int16_t x, int16_t y, int16_t w, int16_t h);
void loadTile(int16_t adr, uint8_t iwidth, uint8_t iheight, uint8_t width, uint8_t height);
void drawTile(int16_t x0, int16_t y0);
void drawFHLine(int16_t x1, int16_t x2, uint16_t y);
void drwLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void setClip(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
uint8_t getPix(uint8_t x, uint8_t y);
void changePalette(uint8_t n, uint16_t c);
void scrollScreen(uint8_t step, uint8_t direction);
void tileDrawLine(uint8_t step, uint8_t direction);
void charLineUp(uint8_t n);
void printc(char c, uint8_t fc, uint8_t bc);
void printfix(int16_t value, uint8_t fc, uint8_t bc);
void drwRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void fillRect(int8_t x, int8_t y, uint8_t w, uint8_t h, uint8_t c);
void fllRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
void drwCirc(int16_t x0, int16_t y0, int16_t r);
void fllCirc(int16_t x0, int16_t y0, int16_t r);
void drwTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);
void fllTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void putString(char s[], int8_t y);
void putchar(char c, uint8_t x, uint8_t y);
void drawChar(uint8_t c, uint16_t x, uint16_t y);
void drawString(uint16_t s, uint16_t x, uint16_t y);
void fontload(int16_t adr, int8_t start, int8_t end);
void fontsize(int16_t imgwidth, int16_t imgheight, int16_t charwidth, int16_t charheight);

inline void setRedrawRect(uint8_t s, uint8_t e)
{
    for (int i = s; i < e; i++)
        SET_LINE_IS_DRAW(i);
}

inline void drawSprPixel(int8_t pixel, int16_t x0, int16_t y0, int16_t x, int16_t y)
{
    if (x0 + x >= 0 && x0 + x < 128 && y0 + y >= 0 && y0 + y < 128)
    {
        if ((x0 + x) & 1)
            sprite_screen[SCREEN_ADDR((x0 + x) / 2, y0 + y)] = (sprite_screen[SCREEN_ADDR((x0 + x) / 2, y0 + y)] & 0xf0) + pixel;
        else
            sprite_screen[SCREEN_ADDR((x0 + x) / 2, y0 + y)] = (sprite_screen[SCREEN_ADDR((x0 + x) / 2, y0 + y)] & 0x0f) + (pixel << 4);
        SET_LINE_IS_DRAW(y0 + y);
    }
}

inline void drawSprFHLine(int16_t x1, int16_t x2, int16_t y, int8_t c)
{
    for (int i = x1; i <= x2; i++)
        drawSprPixel(c, i, y, 0, 0);
}

inline void moveSprites()
{
    for (int i = 0; i < SPRITE_COUNT; i++)
    {
        if (sprite_table[i].lives > 0)
        {
            sprite_table[i].speedy += sprite_table[i].gravity;
            sprite_table[i].x += sprite_table[i].speedx;
            sprite_table[i].y += sprite_table[i].speedy;
        }
    }
}

inline void redrawSprites()
{
    int16_t i, j, ind, tempa, tempb;
    for (i = 0; i < SPRITE_COUNT; i++)
    {
        pix_buffer[i + SPRITE_COUNT] = i;
        pix_buffer[i] = sprite_table[i].zindex;
    }
    for (j = 0; j < SPRITE_COUNT; ++j)
    {
        tempa = pix_buffer[j];
        tempb = pix_buffer[j + SPRITE_COUNT];
        ind = j;
        for (i = j + 1; i < SPRITE_COUNT; ++i)
        {
            if (tempa > pix_buffer[i])
            {
                tempa = pix_buffer[j];
                tempb = pix_buffer[j + SPRITE_COUNT];
                ind = i;
            }
        }
        pix_buffer[ind] = pix_buffer[j];
        pix_buffer[ind + SPRITE_COUNT] = pix_buffer[j + SPRITE_COUNT];
        pix_buffer[j] = tempa;
        pix_buffer[j + SPRITE_COUNT] = tempb;
    }
    for (j = 0; j < SPRITE_COUNT; j++)
    {
        i = pix_buffer[j + SPRITE_COUNT];
        if (sprite_table[i].lives > 0)
        {
            if ((sprite_table[i].x >> 2) + sprite_table[i].width < 0 || (sprite_table[i].x >> 2) > 127 || (sprite_table[i].y >> 2) + sprite_table[i].height < 0 || (sprite_table[i].y >> 2) > 127)
            {
                if (sprite_table[i].onexitscreen > 0)
                    setinterrupt(sprite_table[i].onexitscreen, i);
            }
            else
                drawSpr(i, sprite_table[i].x >> 2, sprite_table[i].y >> 2);
        }
    }
}

inline void testSpriteCollision()
{
    int n, i;
    int16_t x0, y0, x1, y1, newspeed;
    int32_t iwidth, iheight, nwidth, nheight;
    for (n = 0; n < SPRITE_COUNT; n++)
        sprite_table[n].collision = -1;
    for (n = 0; n < SPRITE_COUNT; n++)
    {
        if (sprite_table[n].lives > 0)
        {
            x0 = sprite_table[n].x >> 2;
            y0 = sprite_table[n].y >> 2;
            nwidth = (sprite_table[n].width * sprite_table[n].size) >> fixed_res_bit;
            nheight = (sprite_table[n].height * sprite_table[n].size) >> fixed_res_bit;
            for (i = 0; i < n; i++)
            {
                if (sprite_table[i].lives > 0)
                {
                    x1 = sprite_table[i].x >> 2;
                    y1 = sprite_table[i].y >> 2;
                    iwidth = (sprite_table[i].width * sprite_table[i].size) >> fixed_res_bit;
                    iheight = (sprite_table[i].height * sprite_table[i].size) >> fixed_res_bit;
                    if (x0 < x1 + iwidth && x0 + nwidth > x1 && y0 < y1 + iheight && y0 + nheight > y1)
                    {
                        sprite_table[n].collision = i;
                        sprite_table[i].collision = n;
                        if (sprite_table[n].oncollision > 0)
                            setinterrupt(sprite_table[n].oncollision, n);
                        if (sprite_table[i].oncollision > 0)
                            setinterrupt(sprite_table[i].oncollision, i);
                        if (SPRITE_IS_SOLID(n) && SPRITE_IS_SOLID(i))
                        {
                            resolveCollision(n, i);
                        }
                    }
                }
            }
            if ((SPRITE_IS_SOLID(n)) && tile.adr > 0)
            {
                x0 = sprite_table[n].x >> 2;
                y0 = sprite_table[n].y >> 2;
                if (getTileInXY(x0, y0, tile.collisionMap) || getTileInXY(x0 + nwidth, y0, tile.collisionMap) || getTileInXY(x0, y0 + nheight, tile.collisionMap) || getTileInXY(x0 + nwidth, y0 + nheight, tile.collisionMap))
                {
                    sprite_table[n].y = sprite_table[n].y - sprite_table[n].speedy;
                    sprite_table[n].speedy = sprite_table[n].speedy / 2 - sprite_table[n].gravity;
                    y0 = sprite_table[n].y >> 2;
                    if (getTileInXY(x0, y0, tile.collisionMap) || getTileInXY(x0 + nwidth, y0, tile.collisionMap) || getTileInXY(x0, y0 + nheight, tile.collisionMap) || getTileInXY(x0 + nwidth, y0 + nheight, tile.collisionMap))
                    {
                        sprite_table[n].x = sprite_table[n].x - sprite_table[n].speedx;
                        sprite_table[n].speedx = (sprite_table[n].x - (sprite_table[n].x - sprite_table[n].speedx)) / 2;
                    }
                    x0 = sprite_table[n].x >> 2;
                    y0 = sprite_table[n].y >> 2;
                    if (getTileInXY(x0, y0, tile.collisionMap) || getTileInXY(x0 + nwidth, y0, tile.collisionMap) || getTileInXY(x0, y0 + nheight, tile.collisionMap) || getTileInXY(x0 + nwidth, y0 + nheight, tile.collisionMap))
                    {
                        sprite_table[n].x = sprite_table[n].previousx;
                        sprite_table[n].y = sprite_table[n].previousy;
                    }
                    else
                    {
                        sprite_table[n].previousx = sprite_table[n].x;
                        sprite_table[n].previousy = sprite_table[n].y;
                    }
                }
                else
                {
                    sprite_table[n].previousx = sprite_table[n].x;
                    sprite_table[n].previousy = sprite_table[n].y;
                }
            }
        }
    }
}

inline void clearSpriteScr()
{
    for (int y = 0; y < 128; y++)
        for (int x = 0; x < 64; x += 4)
        {
            if (*((uint32_t *)&sprite_screen[SCREEN_ADDR(x, y)]) > 0)
                SET_LINE_IS_DRAW(y);
        }
    memset(sprite_screen, 0, SCREEN_SIZE);
}

inline void setImageSize(uint16_t size)
{
    imageSize = size & 0x7fff;
}

inline void setSpr(uint16_t n, uint16_t adr)
{
    sprite_table[n].address = adr;
}

inline void setSprWidth(uint16_t n, uint8_t w)
{
    sprite_table[n].width = w;
}

inline void setSprHeight(uint16_t n, uint8_t w)
{
    sprite_table[n].height = w;
}

inline void setSprSize(uint16_t n, uint16_t s)
{
    sprite_table[n].size = s & 0x7fff;
}

inline void setSprSpeedx(uint16_t n, int8_t s)
{
    sprite_table[n].speedx = s;
}

inline void setSprSpeedy(uint16_t n, int8_t s)
{
    sprite_table[n].speedy = s;
}

inline void drawRotateSprPixel(int8_t pixel, int16_t x0, int16_t y0, int16_t x, int16_t y, int16_t hw, int16_t hh, int16_t c, int16_t s)
{
    int16_t nx = hw + (((x - hw) * c - (y - hh) * s) >> fixed_res_bit);
    int16_t ny = hh + (((y - hh) * c + (x - hw) * s) >> fixed_res_bit);
    int16_t nnx = nx / 2;
    int16_t nnx0 = x0 / 2;
    if (nnx0 + nnx >= 0 && nnx0 + nnx < 64 && y0 + ny >= 0 && y0 + ny < 128)
    {
        if (nx & 1)
            sprite_screen[SCREEN_ADDR(nnx0 + nnx, y0 + ny)] = (sprite_screen[SCREEN_ADDR(nnx0 + nnx, y0 + ny)] & 0xf0) + pixel;
        else
            sprite_screen[SCREEN_ADDR(nnx0 + nnx, y0 + ny)] = (sprite_screen[SCREEN_ADDR(nnx0 + nnx, y0 + ny)] & 0x0f) + (pixel << 4);
        SET_LINE_IS_DRAW(y0 + ny);
    }
}

inline void setPix(uint16_t x, uint16_t y, uint8_t c)
{
    uint16_t xi, b, n;
    if (isClip)
    {
        if (x < clipx1 && x >= clipx0 && y < clipy1 && y >= clipy0)
        {
            xi = x >> 1;
            b = screen[SCREEN_ADDR(xi, y)];
            if (x & 1)
                n = (b & 0xf0) + c;
            else
                n = (b & 0x0f) + (c << 4);
            if (b != n)
            {
                SET_LINE_IS_DRAW(y);
                screen[SCREEN_ADDR(xi, y)] = n;
            }
        }
    }
    else
    {
        if (x < 128 && y < 128)
        {
            xi = x >> 1;
            b = screen[SCREEN_ADDR(xi, y)];
            if (x & 1)
                n = (b & 0xf0) + c;
            else
                n = (b & 0x0f) + (c << 4);
            if (b != n)
            {
                SET_LINE_IS_DRAW(y);
                screen[SCREEN_ADDR(xi, y)] = n;
            }
        }
    }
}

inline void drawFVLine(int x, int y1, int y2)
{
    for (int i = y1; i <= y2; i++)
        setPix(x, i, color);
}

inline void setCharX(int8_t x)
{
    regx = x;
}

inline void setCharY(int8_t y)
{
    regy = y;
}

inline int8_t getCharY()
{
    return regy;
}

inline void setColor(uint8_t c)
{
    color = c & 0xf;
}

inline void setBgColor(uint8_t c)
{
    bgcolor = c & 0xf;
}
#endif // DISPLAY_HPP