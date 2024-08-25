//TODO: Remove virtual keyboard stuff
#include "display.h"
#include "font_a.c"
#include "sound.h"
#include "io.h"
#include "esp_lge.h"
#include "file_manager.h"
#include "lge_memory.h"
#include "cpu.h"
#include "progmem/pauseImage.h"
#include "progmem/keyboardImage.h"
#include "progmem/color_palette.h"

#define SPRITE_IS_SOLID(a) (sprite_table[a].flags & 1)
#define SPRITE_IS_SCROLLED(a) (sprite_table[a].flags & 2)
#define SPRITE_IS_ONEBIT(a) (sprite_table[a].flags & 4)
#define SPRITE_IS_FLIP_HORIZONTAL(a) (sprite_table[a].flags & 8)
#define SET_LINE_IS_DRAW(a) line_is_draw[(a) >> 5] |= (1 << ((a)&31))

uint16_t displayXOffset = 32;
int16_t imageSize = 1;
int8_t regx = 0;
int8_t regy = 0;
int8_t isDrawKeyboard = 0;
int8_t keyboardPos = 0;
uint8_t clipx0 = 0;
uint8_t clipx1 = 128;
uint8_t clipy0 = 0;
uint8_t clipy1 = 128;
uint8_t isClip = 0;

#pragma GCC optimize("-O2")
#pragma GCC push_options

void screenMemoryAlloc() {
  screen = (uint8_t *)malloc(SCREEN_ARRAY_DEF * sizeof(uint8_t));
  if (screen == NULL)
    Serial.println(F("Out of memory"));
  sprite_screen = (uint8_t *)malloc(SCREEN_ARRAY_DEF * sizeof(uint8_t));
  if (sprite_screen == NULL)
    Serial.println(F("Out of memory"));
}

void screenMemoryFree() {
  free(screen);
  free(sprite_screen);
}

int16_t atan2_fp(int16_t y_fp, int16_t x_fp) {
  int32_t coeff_1 = 45;
  int32_t coeff_1b = -56;  // 56.24;
  int32_t coeff_1c = 11;   // 11.25
  int16_t coeff_2 = 135;
  int16_t angle = 0;
  int32_t r;
  int32_t r3;
  int16_t y_abs_fp = y_fp;
  if (y_abs_fp < 0)
    y_abs_fp = -y_abs_fp;
  if (y_fp == 0) {
    if (x_fp >= 0) {
      angle = 0;
    } else {
      angle = 180;
    }
  } else if (x_fp >= 0) {
    r = (((int32_t)(x_fp - y_abs_fp)) << MULTIPLY_FP_RESOLUTION_BITS) / ((int32_t)(x_fp + y_abs_fp));
    r3 = r * r;
    r3 = r3 >> MULTIPLY_FP_RESOLUTION_BITS;
    r3 *= r;
    r3 = r3 >> MULTIPLY_FP_RESOLUTION_BITS;
    r3 *= coeff_1c;
    angle = (int16_t)(coeff_1 + ((coeff_1b * r + r3) >> MULTIPLY_FP_RESOLUTION_BITS));
  } else {
    r = (((int32_t)(x_fp + y_abs_fp)) << MULTIPLY_FP_RESOLUTION_BITS) / ((int32_t)(y_abs_fp - x_fp));
    r3 = r * r;
    r3 = r3 >> MULTIPLY_FP_RESOLUTION_BITS;
    r3 *= r;
    r3 = r3 >> MULTIPLY_FP_RESOLUTION_BITS;
    r3 *= coeff_1c;
    angle = coeff_2 + ((int16_t)(((coeff_1b * r + r3) >> MULTIPLY_FP_RESOLUTION_BITS)));
  }
  if (y_fp < 0)
    return (-angle);  // negate if in quad III or IV
  else
    return (angle);
}

void display_init() {
  for (int i = 0; i < SPRITE_COUNT; i++) {
    sprite_table[i].address = 0;
    sprite_table[i].x = -255;
    sprite_table[i].y = -255;
    sprite_table[i].previousx = -255;
    sprite_table[i].previousy = -255;
    sprite_table[i].width = 8;
    sprite_table[i].height = 8;
    sprite_table[i].size = 1 << fixed_res_bit;
    sprite_table[i].speedx = 0;
    sprite_table[i].speedy = 0;
    sprite_table[i].angle = 0;
    sprite_table[i].lives = 0;
    sprite_table[i].collision = -1;
    sprite_table[i].flags = 18;  //color = 1 isonebit = 0 scrolled = 1 solid = 0
    sprite_table[i].gravity = 0;
    sprite_table[i].oncollision = 0;
    sprite_table[i].onexitscreen = 0;
  }
  for (int i = 0; i < 16; i++) {
    palette[i] = pgm_read_word(&bpalette[i]);
    sprtpalette[i] = pgm_read_word(&bpalette[i]);
  }
  emitter.time = 0;
  emitter.timer = 0;
  emitter.size = 0;
  emitter.width = 0;
  emitter.height = 0;
  uint8_t clipx0 = 0;
  uint8_t clipx1 = 128;
  uint8_t clipy0 = 0;
  uint8_t clipy1 = 128;
  tile.adr = 0;
  tile.collisionMap = 0;
  for (int8_t i = 0; i < PARTICLE_COUNT; i++)
    particles[i].time = 0;
  for (uint16_t i = 0; i < 340; i++)
    charArray[i] = 0;
  imageSize = 1;
  regx = 0;
  regy = 0;
  custom_font.address = 0;
  custom_font.start = 0;
  custom_font.end = 255;
  custom_font.imgwidth = 0;
  custom_font.imgheight = 0;
  custom_font.charwidth = 6;
  custom_font.charheight = 8;
  custom_font.columns = 0;
  timeForRedraw = 48;
}

char pause() {
  uint8_t prevKey = 192;
  noTone(SOUNDPIN);
  drawPause();
  redrawScreen();
  while (1) {
    delay(100);
    getKey();
    if ((thiskey & 192) && prevKey != 192) {
      thiskey = 0;
      delay(800);
      return 0;
    }
    if (thiskey & 16) {
      clearSpriteScr();
      while (thiskey & 16) {
        delay(100);
        getKey();
      }
      thiskey = 0;
      serial_used = 0;
      fileList("/");
      return 1;
    }
    prevKey = thiskey;
  }
}

void drawPause() {
  int i = 0;
  uint8_t bit;
  uint16_t adr = 0;
  for (int y = 0; y < 30; y++)
    for (int x = 0; x < 32; x++) {
      if (i % 8 == 0) {
        bit = pgm_read_byte_near(pauseImage + adr);
        adr++;
      }
      if (bit & 0x80)
        drawSprPixel(1, 48, 48, x, y);
      else
        drawSprPixel(11, 48, 48, x, y);
      bit = bit << 1;
      i++;
    }
}

int randomD(int a, int b) {
  int minv = a < b ? a : b;
  int maxv = a > b ? a : b;
  return random(minv, maxv + 1);
}

void setParticle(int8_t gravity, uint8_t count, uint16_t time) {
  emitter.gravity = gravity;
  emitter.count = count;
  emitter.timeparticle = time;
}

void setEmitter(uint16_t time, int16_t dir, int16_t dir1, int16_t speed) {
  dir = dir % 360;
  if (dir < 0)
    dir += 360;
  emitter.time = time;
  emitter.speedx = (int8_t)((speed * fixed_cos(dir)) >> fixed_res_bit);
  emitter.speedy = (int8_t)((speed * fixed_sin(dir)) >> fixed_res_bit);
  emitter.speedx1 = (int8_t)((speed * fixed_cos(dir1)) >> fixed_res_bit);
  emitter.speedy1 = (int8_t)((speed * fixed_sin(dir1)) >> fixed_res_bit);
}

void setEmitterSize(uint8_t width, uint8_t height, uint8_t size) {
  emitter.width = width << 1;
  emitter.height = height << 1;
  emitter.size = size;
}

void drawParticle(int16_t x, int16_t y, uint8_t color) {
  emitter.x = x << 1;
  emitter.y = y << 1;
  emitter.color = color;
  emitter.timer = emitter.time;
  updateEmitter();
}

void setScreenResolution(uint16_t nw, uint16_t nh) {
  if (nw < SCREEN_REAL_WIDTH)
    rscreenWidth = nw;
  else
    rscreenWidth = SCREEN_REAL_WIDTH - 1;
  if (nh < SCREEN_REAL_HEIGHT)
    rscreenHeight = nh;
  else
    rscreenHeight = SCREEN_REAL_HEIGHT - 1;
  if (rscreenWidth < 95)
    rscreenWidth = 95;
  if (rscreenHeight < 95)
    rscreenHeight = 95;
  displayXOffset = (SCREEN_REAL_WIDTH - rscreenWidth) / 2;
  for (int i = 0; i < 4; i++)
    line_is_draw[i] = 0xffffffff;
  tft.fillScreen(0x0000);
}

uint16_t getDisplayXOffset() {
  return displayXOffset;
}

void redrawScreen() {
  int x_ratio = (int)((128 << 16) / rscreenWidth);
  int y_ratio = (int)((128 << 16) / rscreenHeight);
  int x2, hx2, y2, startx, endx, j;
  int prevy2 = -1;
  for (int i = 0; i < rscreenHeight; i++) {
    y2 = ((i * y_ratio) >> 16);
    if (line_is_draw[y2 >> 5] & (1 << (y2 & 31))) {
      startx = displayXOffset;
      endx = displayXOffset + rscreenWidth;
      tft.setAddrWindow(startx, i, endx, i + 1);
      if (prevy2 != y2)
        for (uint16_t j = 0; j < rscreenWidth; j++) {
          x2 = ((j * x_ratio) >> 16);
          hx2 = x2 / 2;
          if (x2 & 1) {
            if ((sprite_screen[SCREEN_ADDR(hx2, y2)] & 0xf))
              pix_buffer[j] = sprtpalette[(sprite_screen[SCREEN_ADDR(hx2, y2)] & 0xf)];
            else
              pix_buffer[j] = palette[(screen[SCREEN_ADDR(hx2, y2)] & 0xf)];
          } else {
            if ((sprite_screen[SCREEN_ADDR(hx2, y2)] & 0xf0))
              pix_buffer[j] = sprtpalette[(sprite_screen[SCREEN_ADDR(hx2, y2)] & 0xf0) >> 4];
            else
              pix_buffer[j] = palette[(screen[SCREEN_ADDR(hx2, y2)] & 0xf0) >> 4];
          }
        }
      prevy2 = y2;
      tft.pushColors(pix_buffer, endx - startx);
    }
  }
  for (uint16_t i = 0; i < 4; i++)
    line_is_draw[i] = 0;
}

inline void setRedrawRect(uint8_t s, uint8_t e) {
  for (int i = s; i < e; i++)
    SET_LINE_IS_DRAW(i);
}

inline void drawSprFHLine(int16_t x1, int16_t x2, int16_t y, int8_t c) {
  for (int i = x1; i <= x2; i++)
    drawSprPixel(c, i, y, 0, 0);
}

void largeParticle(int16_t x0, int16_t y0, int16_t r, int8_t c) {
  int16_t x = 0;
  int16_t dx = 1;
  int16_t dy = r + r;
  int16_t p = -(r >> 1);

  drawSprFHLine(x0 - r, x0 + r, y0, c);

  while (x < r) {
    if (p >= 0) {
      dy -= 2;
      p -= dy;
      r--;
    }

    dx += 2;
    p += dx;

    x++;

    drawSprFHLine(x0 - r, x0 + r, y0 + x, c);
    drawSprFHLine(x0 - r, x0 + r, y0 - x, c);
    drawSprFHLine(x0 - x, x0 + x, y0 + r, c);
    drawSprFHLine(x0 - x, x0 + x, y0 - r, c);
  }
}

void updateEmitter() {
  int i, n;
  i = emitter.count;
  for (n = 0; n < PARTICLE_COUNT; n++) {
    if (i == 0)
      break;
    if (particles[n].time <= 0) {
      i--;
      particles[n].time = emitter.timeparticle;
      particles[n].x = emitter.x + random(emitter.width);
      particles[n].y = emitter.y + random(emitter.height);
      particles[n].color = emitter.color;
      particles[n].size = emitter.size;
      particles[n].speedx = randomD(emitter.speedx, emitter.speedx1);
      particles[n].speedy = randomD(emitter.speedy, emitter.speedy1);
      particles[n].gravity = emitter.gravity;
    }
  }
}

void redrawParticles() {
  uint16_t n;
  uint16_t x, y;
  if (emitter.timer > 0) {
    emitter.timer -= 50;
    updateEmitter();
  }
  for (n = 0; n < PARTICLE_COUNT; n++)
    if (particles[n].time > 0) {
      x = ((particles[n].x >> 1) & 127);
      y = (particles[n].y >> 1) & 127;
      if (particles[n].size) {
        largeParticle(x, y, particles[n].size, particles[n].color);
      } else {
        x = x >> 1;
        if (particles[n].x & 1)
          sprite_screen[SCREEN_ADDR(x, y)] = (sprite_screen[SCREEN_ADDR(x, y)] & 0xf0) + (particles[n].color & 0x0f);
        else
          sprite_screen[SCREEN_ADDR(x, y)] = (sprite_screen[SCREEN_ADDR(x, y)] & 0x0f) + ((particles[n].color & 0x0f) << 4);
        SET_LINE_IS_DRAW(y);
      }
      particles[n].time -= 50;
      if (random(0, 2)) {
        particles[n].x += particles[n].speedx;
        particles[n].speedy += particles[n].gravity;
        particles[n].y += particles[n].speedy;
      } else {
        particles[n].x += particles[n].speedx / 2;
        particles[n].y += particles[n].speedy / 2;
      }
      if (particles[n].x < 0 || particles[n].x > 256 || particles[n].y < 0 || particles[n].y > 256)
        particles[n].time = 0;
    }
}

int16_t getSpriteInXY(int16_t x, int16_t y) {
  for (int n = 0; n < SPRITE_COUNT; n++) {
    if (sprite_table[n].lives > 0)
      if ((sprite_table[n].x >> 2) < x && (sprite_table[n].x >> 2) + sprite_table[n].width > x && (sprite_table[n].y >> 2) < y && (sprite_table[n].y >> 2) + sprite_table[n].height > y)
        return n;
  }
  return -1;
}

inline void moveSprites() {
  for (int i = 0; i < SPRITE_COUNT; i++) {
    if (sprite_table[i].lives > 0) {
      sprite_table[i].speedy += sprite_table[i].gravity;
      sprite_table[i].x += sprite_table[i].speedx;
      sprite_table[i].y += sprite_table[i].speedy;
    }
  }
}

inline void redrawSprites() {
  int16_t i, j, ind, tempa, tempb;
  for (i = 0; i < SPRITE_COUNT; i++) {
    pix_buffer[i + SPRITE_COUNT] = i;
    pix_buffer[i] = sprite_table[i].zindex;
  }
  for (j = 0; j < SPRITE_COUNT; ++j) {
    tempa = pix_buffer[j];
    tempb = pix_buffer[j + SPRITE_COUNT];
    ind = j;
    for (i = j + 1; i < SPRITE_COUNT; ++i) {
      if (tempa > pix_buffer[i]) {
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
  for (j = 0; j < SPRITE_COUNT; j++) {
    i = pix_buffer[j + SPRITE_COUNT];
    if (sprite_table[i].lives > 0) {
      if ((sprite_table[i].x >> 2) + sprite_table[i].width < 0 || (sprite_table[i].x >> 2) > 127
          || (sprite_table[i].y >> 2) + sprite_table[i].height < 0 || (sprite_table[i].y >> 2) > 127) {
        if (sprite_table[i].onexitscreen > 0)
          setinterrupt(sprite_table[i].onexitscreen, i);
      } else
        drawSpr(i, sprite_table[i].x >> 2, sprite_table[i].y >> 2);
    }
  }
}

void setTileCollisionMap(int16_t adr) {
  tile.collisionMap = adr;
}

uint16_t getTileInXY(int16_t x, int16_t y, int16_t collisionMapAdr) {
  uint32_t p;
  if (x < tile.x || y < tile.y || x > tile.x + tile.pixwidth || y > tile.y + tile.pixheight)
    return 0;
  p = ((x - tile.x) / (int16_t)tile.imgwidth) + ((y - tile.y) / (int16_t)tile.imgheight * (int16_t)tile.width);
  if (collisionMapAdr > 0)
    return readInt(collisionMapAdr + p / 8) & (1 << (7 - (p & 7)));
  else
    return readInt(tile.adr + p * 2);
}

void resolveCollision(uint8_t n, uint8_t i) {
  int startx, starty, startix, startiy;
  startx = sprite_table[n].x;
  starty = sprite_table[n].y;
  startix = sprite_table[i].x;
  startiy = sprite_table[i].y;
  sprite_table[n].x = sprite_table[n].x - sprite_table[n].speedx;
  sprite_table[n].y = sprite_table[n].y - sprite_table[n].speedy;
  sprite_table[i].x = sprite_table[i].x - sprite_table[i].speedx;
  sprite_table[i].y = sprite_table[i].y - sprite_table[i].speedy;
  if ((sprite_table[n].speedy >= 0 && sprite_table[i].speedy <= 0) || (sprite_table[n].speedy <= 0 && sprite_table[i].speedy >= 0)) {
    if (sprite_table[n].y > sprite_table[i].y) {
      if (sprite_table[i].gravity) {
        sprite_table[i].y = sprite_table[n].y - (sprite_table[i].height << 2);
      }
    } else {
      if (sprite_table[n].gravity) {
        sprite_table[n].y = sprite_table[i].y - (sprite_table[n].height << 2);
      }
    }
  }
  if (sprite_table[n].x < sprite_table[i].x + (sprite_table[i].width << 2) && sprite_table[n].x + (sprite_table[n].width << 2) > sprite_table[i].x && sprite_table[n].y < sprite_table[i].y + (sprite_table[i].height << 2) && sprite_table[n].y + (sprite_table[n].height << 2) > sprite_table[i].y) {
    if (sprite_table[n].x > sprite_table[i].x) {
      sprite_table[n].x++;
      sprite_table[i].x--;
    } else {
      sprite_table[n].x--;
      sprite_table[i].x++;
    }
    if (sprite_table[n].y > sprite_table[i].y) {
      sprite_table[n].y++;
      sprite_table[i].y--;
    } else {
      sprite_table[n].y--;
      sprite_table[i].y++;
    }
  }
  if (sprite_table[n].gravity) {
    sprite_table[n].speedx = (sprite_table[n].x - startx) / 4;
    sprite_table[n].speedy = (sprite_table[n].y - starty) / 4;
  } else {
    sprite_table[n].speedx = sprite_table[n].x - startx;
    sprite_table[n].speedy = sprite_table[n].y - starty;
  }
  if (sprite_table[i].gravity) {
    sprite_table[i].speedx = (sprite_table[i].x - startix) / 4;
    sprite_table[i].speedy = (sprite_table[i].y - startiy) / 4;
  } else {
    sprite_table[i].speedx = sprite_table[i].x - startix;
    sprite_table[i].speedy = sprite_table[i].y - startiy;
  }
}

inline void testSpriteCollision() {
  int n, i;
  int16_t x0, y0, x1, y1, newspeed;
  int32_t iwidth, iheight, nwidth, nheight;
  for (n = 0; n < SPRITE_COUNT; n++)
    sprite_table[n].collision = -1;
  for (n = 0; n < SPRITE_COUNT; n++) {
    if (sprite_table[n].lives > 0) {
      x0 = sprite_table[n].x >> 2;
      y0 = sprite_table[n].y >> 2;
      nwidth = (sprite_table[n].width * sprite_table[n].size) >> fixed_res_bit;
      nheight = (sprite_table[n].height * sprite_table[n].size) >> fixed_res_bit;
      for (i = 0; i < n; i++) {
        if (sprite_table[i].lives > 0) {
          x1 = sprite_table[i].x >> 2;
          y1 = sprite_table[i].y >> 2;
          iwidth = (sprite_table[i].width * sprite_table[i].size) >> fixed_res_bit;
          iheight = (sprite_table[i].height * sprite_table[i].size) >> fixed_res_bit;
          if (x0 < x1 + iwidth && x0 + nwidth > x1
              && y0 < y1 + iheight && y0 + nheight > y1) {
            sprite_table[n].collision = i;
            sprite_table[i].collision = n;
            if (sprite_table[n].oncollision > 0)
              setinterrupt(sprite_table[n].oncollision, n);
            if (sprite_table[i].oncollision > 0)
              setinterrupt(sprite_table[i].oncollision, i);
            if (SPRITE_IS_SOLID(n) && SPRITE_IS_SOLID(i)) {
              resolveCollision(n, i);
            }
          }
        }
      }
      if ((SPRITE_IS_SOLID(n)) && tile.adr > 0) {
        x0 = sprite_table[n].x >> 2;
        y0 = sprite_table[n].y >> 2;
        if (getTileInXY(x0, y0, tile.collisionMap) || getTileInXY(x0 + nwidth, y0, tile.collisionMap)
            || getTileInXY(x0, y0 + nheight, tile.collisionMap) || getTileInXY(x0 + nwidth, y0 + nheight, tile.collisionMap)) {
          sprite_table[n].y = sprite_table[n].y - sprite_table[n].speedy;
          sprite_table[n].speedy = sprite_table[n].speedy / 2 - sprite_table[n].gravity;
          y0 = sprite_table[n].y >> 2;
          if (getTileInXY(x0, y0, tile.collisionMap) || getTileInXY(x0 + nwidth, y0, tile.collisionMap)
              || getTileInXY(x0, y0 + nheight, tile.collisionMap) || getTileInXY(x0 + nwidth, y0 + nheight, tile.collisionMap)) {
            sprite_table[n].x = sprite_table[n].x - sprite_table[n].speedx;
            sprite_table[n].speedx = (sprite_table[n].x - (sprite_table[n].x - sprite_table[n].speedx)) / 2;
          }
          x0 = sprite_table[n].x >> 2;
          y0 = sprite_table[n].y >> 2;
          if (getTileInXY(x0, y0, tile.collisionMap) || getTileInXY(x0 + nwidth, y0, tile.collisionMap)
              || getTileInXY(x0, y0 + nheight, tile.collisionMap) || getTileInXY(x0 + nwidth, y0 + nheight, tile.collisionMap)) {
            sprite_table[n].x = sprite_table[n].previousx;
            sprite_table[n].y = sprite_table[n].previousy;
          } else {
            sprite_table[n].previousx = sprite_table[n].x;
            sprite_table[n].previousy = sprite_table[n].y;
          }
        } else {
          sprite_table[n].previousx = sprite_table[n].x;
          sprite_table[n].previousy = sprite_table[n].y;
        }
      }
    }
  }
}

inline void clearSpriteScr() {
  for (int y = 0; y < 128; y++)
    for (int x = 0; x < 64; x += 4) {
      if (*((uint32_t *)&sprite_screen[SCREEN_ADDR(x, y)]) > 0)
        SET_LINE_IS_DRAW(y);
    }
  memset(sprite_screen, 0, SCREEN_SIZE);
}

void clearScr(uint8_t color) {
  for (int y = 0; y < 128; y++) {
    for (int x = 0; x < 128; x++)
      setPix(x, y, color);
  }
}

void spriteDebug() {
  int i;
  for (i = 0; i < SPRITE_COUNT; i++) {
    Serial.print(sprite_table[i].address);
    Serial.print(':');
  }
  Serial.println();
}

inline void setImageSize(uint16_t size) {
  imageSize = size & 0x7fff;
}

inline void setSpr(uint16_t n, uint16_t adr) {
  sprite_table[n].address = adr;
}

void setSprPosition(uint16_t n, uint16_t x, uint16_t y) {
  sprite_table[n].x = x << 2;
  sprite_table[n].y = y << 2;
  sprite_table[n].previousx = x << 2;
  sprite_table[n].previousy = y << 2;
}

void spriteSetDirectionAndSpeed(uint16_t n, uint16_t speed, int16_t dir) {
  dir = dir % 360;
  if (dir < 0)
    dir += 360;
  sprite_table[n].speedx = ((speed * fixed_cos(dir)) >> fixed_res_bit);
  sprite_table[n].speedy = ((speed * fixed_sin(dir)) >> fixed_res_bit);
}

inline void setSprWidth(uint16_t n, uint8_t w) {
  sprite_table[n].width = w;
}

inline void setSprHeight(uint16_t n, uint8_t w) {
  sprite_table[n].height = w;
}

inline void setSprSize(uint16_t n, uint16_t s) {
  sprite_table[n].size = s & 0x7fff;
}

inline void setSprSpeedx(uint16_t n, int8_t s) {
  sprite_table[n].speedx = s;
}

inline void setSprSpeedy(uint16_t n, int8_t s) {
  sprite_table[n].speedy = s;
}

int16_t angleBetweenSprites(uint16_t n1, int8_t n2) {
  int16_t A = atan2_fp(sprite_table[n1].y - sprite_table[n2].y, sprite_table[n1].x - sprite_table[n2].x);
  A = (A < 0) ? A + 360 : A;
  return A;
}

int16_t getSpriteValue(uint16_t n, uint16_t t) {
  switch (t) {
    case 0:
      return sprite_table[n].x >> 2;
    case 1:
      return sprite_table[n].y >> 2;
    case 2:
      return sprite_table[n].speedx;
    case 3:
      return sprite_table[n].speedy;
    case 4:
      return sprite_table[n].width;
    case 5:
      return sprite_table[n].height;
    case 6:
      return sprite_table[n].angle;
    case 7:
      return sprite_table[n].lives;
    case 8:
      return sprite_table[n].collision;
    case 9:
      return SPRITE_IS_SCROLLED(2);
    case 10:
      return sprite_table[n].gravity;
  }
  return 0;
}

void setSpriteValue(uint16_t n, uint16_t t, int16_t v) {
  switch (t) {
    case 0:
      sprite_table[n].x = v << 2;
      return;
    case 1:
      sprite_table[n].y = v << 2;
      return;
    case 2:
      sprite_table[n].speedx = (int8_t)v;
      return;
    case 3:
      sprite_table[n].speedy = (int8_t)v;
      return;
    case 4:
      sprite_table[n].width = v;
      return;
    case 5:
      sprite_table[n].height = v;
      return;
    case 6:
      v = v % 360;
      if (v < 0)
        v += 360;
      sprite_table[n].angle = v;
      return;
    case 7:
      sprite_table[n].lives = v;
      return;
    case 8:
      return;
    case 9:
      if (v != 0)
        sprite_table[n].flags |= 0x01;
      else
        sprite_table[n].flags &= ~0x01;
      return;
    case 10:
      sprite_table[n].gravity = v;
      return;
    case 11:
      sprite_table[n].oncollision = (uint16_t)v;
      return;
    case 12:
      sprite_table[n].onexitscreen = (uint16_t)v;
      return;
    case 13:
      if (v != 0)
        sprite_table[n].flags |= 0x02;
      else
        sprite_table[n].flags &= ~0x02;
      return;
    case 14:
      if (v != 0)
        sprite_table[n].flags |= 0x04;
      else
        sprite_table[n].flags &= ~0x04;
      return;
    case 15:
      if (v != 0)
        sprite_table[n].flags |= 0x08;
      else
        sprite_table[n].flags &= ~0x08;
      return;
    case 16:
      sprite_table[n].zindex = (uint8_t)v;
      return;
    case 17:
      sprite_table[n].flags &= 0x0f;
      sprite_table[n].flags |= (uint8_t)v << 4;
      return;
  }
}

inline void drawRotateSprPixel(int8_t pixel, int16_t x0, int16_t y0, int16_t x, int16_t y, int16_t hw, int16_t hh, int16_t c, int16_t s) {
  int16_t nx = hw + (((x - hw) * c - (y - hh) * s) >> fixed_res_bit);
  int16_t ny = hh + (((y - hh) * c + (x - hw) * s) >> fixed_res_bit);
  int16_t nnx = nx / 2;
  int16_t nnx0 = x0 / 2;
  if (nnx0 + nnx >= 0 && nnx0 + nnx < 64 && y0 + ny >= 0 && y0 + ny < 128) {
    if (nx & 1)
      sprite_screen[SCREEN_ADDR(nnx0 + nnx, y0 + ny)] = (sprite_screen[SCREEN_ADDR(nnx0 + nnx, y0 + ny)] & 0xf0) + pixel;
    else
      sprite_screen[SCREEN_ADDR(nnx0 + nnx, y0 + ny)] = (sprite_screen[SCREEN_ADDR(nnx0 + nnx, y0 + ny)] & 0x0f) + (pixel << 4);
    SET_LINE_IS_DRAW(y0 + ny);
  }
}

inline void drawSprPixel(int8_t pixel, int16_t x0, int16_t y0, int16_t x, int16_t y) {
  if (x0 + x >= 0 && x0 + x < 128 && y0 + y >= 0 && y0 + y < 128) {
    if ((x0 + x) & 1)
      sprite_screen[SCREEN_ADDR((x0 + x) / 2, y0 + y)] = (sprite_screen[SCREEN_ADDR((x0 + x) / 2, y0 + y)] & 0xf0) + pixel;
    else
      sprite_screen[SCREEN_ADDR((x0 + x) / 2, y0 + y)] = (sprite_screen[SCREEN_ADDR((x0 + x) / 2, y0 + y)] & 0x0f) + (pixel << 4);
    SET_LINE_IS_DRAW(y0 + y);
  }
}

void drawSpr(int16_t n, int16_t x, int16_t y) {
  uint16_t adr = sprite_table[n].address;
  uint16_t w = sprite_table[n].width;
  uint16_t h = sprite_table[n].height;
  uint16_t ww = w;
  int16_t c, s;
  uint16_t sz, x1, y1, x2, y2, endx, endy, i;
  uint8_t pixel, ibit;
  w = w / 2;
  sz = sprite_table[n].size;
  if (!SPRITE_IS_ONEBIT(n)) {
    if (!sprite_table[n].angle) {
      if (SPRITE_IS_FLIP_HORIZONTAL(n)) {
        if (sz != 1 << fixed_res_bit) {
          endx = ((ww * sz) >> fixed_res_bit);
          for (y1 = 0; y1 < ((h * sz) >> fixed_res_bit); y1++) {
            y2 = ((y1 << fixed_res_bit) + 1) / sz;
            if ((y + y1) > 128)
              return;
            for (x1 = 0; x1 < endx; x1++) {
              x2 = ((x1 << fixed_res_bit) + 1) / sz;
              pixel = readMem(adr + x2 / 2 + (y2 * ww) / 2);
              if (x2 & 1) {
                pixel = (pixel & 0x0f);
              } else {
                pixel = (pixel & 0xf0) >> 4;
              }
              if (pixel)
                drawSprPixel(pixel, x, y, endx - x1, y1);
            }
          }
        } else {
          for (y1 = 0; y1 < h; y1++) {
            if (y1 + y >= -h && y1 + y < 128 + h) {
              for (x1 = 0; x1 < w; x1++) {
                pixel = readMem(adr + x1 + y1 * w);
                if ((pixel & 0xf0) > 0)
                  drawSprPixel(pixel >> 4, x, y, ww - x1 * 2, y1);
                if ((pixel & 0x0f) > 0)
                  drawSprPixel(pixel & 0xf, x, y, ww - (x1 * 2 + 1), y1);
              }
            }
          }
        }
      } else {
        if (sz != 1 << fixed_res_bit) {
          endx = ((ww * sz) >> fixed_res_bit);
          for (y1 = 0; y1 < ((h * sz) >> fixed_res_bit); y1++) {
            y2 = ((y1 << fixed_res_bit) + 1) / sz;
            if ((y + y1) > 128)
              return;
            for (x1 = 0; x1 < endx; x1++) {
              x2 = ((x1 << fixed_res_bit) + 1) / sz;
              pixel = readMem(adr + x2 / 2 + (y2 * ww) / 2);
              if (x2 & 1) {
                pixel = (pixel & 0x0f);
              } else {
                pixel = (pixel & 0xf0) >> 4;
              }
              if (pixel)
                drawSprPixel(pixel, x, y, x1, y1);
            }
          }
        } else {
          for (y1 = 0; y1 < h; y1++) {
            if (y1 + y >= -h && y1 + y < 128 + h) {
              for (x1 = 0; x1 < w; x1++) {
                pixel = readMem(adr + x1 + y1 * w);
                if ((pixel & 0xf0) > 0)
                  drawSprPixel(pixel >> 4, x, y, x1 * 2, y1);
                if ((pixel & 0x0f) > 0)
                  drawSprPixel(pixel & 0xf, x, y, x1 * 2 + 1, y1);
              }
            }
          }
        }
      }
    } else {
      c = fixed_cos(sprite_table[n].angle);
      s = fixed_sin(sprite_table[n].angle);
      if (SPRITE_IS_FLIP_HORIZONTAL(n)) {
        if (sz != 1 << fixed_res_bit) {
          endx = ((ww * sz) >> fixed_res_bit);
          endy = ((h * sz / 2) >> fixed_res_bit);
          for (y1 = 0; y1 < ((h * sz) >> fixed_res_bit); y1++) {
            y2 = ((y1 << fixed_res_bit) + 1) / sz;
            if ((y + y1) > 128)
              return;
            for (x1 = 0; x1 < endx; x1++) {
              x2 = ((x1 << fixed_res_bit) + 1) / sz;
              pixel = readMem(adr + x2 / 2 + (y2 * ww) / 2);
              if (x2 & 1) {
                pixel = (pixel & 0x0f);
              } else {
                pixel = (pixel & 0xf0) >> 4;
              }
              if (pixel)
                drawRotateSprPixel(pixel, x, y, endx - x1, y1, endx / 2, endy, c, s);
            }
          }
        } else {
          for (y1 = 0; y1 < h; y1++) {
            if (y1 + y >= -h && y1 + y < 128 + h) {
              for (x1 = 0; x1 < w; x1++) {
                if (x1 + x >= -w && x1 + x < 128 + w) {
                  pixel = readMem(adr + x1 + y1 * w);
                  if ((pixel & 0xf0) > 0)
                    drawRotateSprPixel(pixel >> 4, x, y, ww - x1 * 2, y1, w, h / 2, c, s);
                  if ((pixel & 0x0f) > 0)
                    drawRotateSprPixel(pixel & 0xf, x, y, ww - (x1 * 2 + 1), y1, w, h / 2, c, s);
                }
              }
            }
          }
        }
      } else {
        if (sz != 1 << fixed_res_bit) {
          endx = ((ww * sz) >> fixed_res_bit);
          endy = ((h * sz / 2) >> fixed_res_bit);
          for (y1 = 0; y1 < ((h * sz) >> fixed_res_bit); y1++) {
            y2 = ((y1 << fixed_res_bit) + 1) / sz;
            if ((y + y1) > 128)
              return;
            for (x1 = 0; x1 < endx; x1++) {
              x2 = ((x1 << fixed_res_bit) + 1) / sz;
              pixel = readMem(adr + x2 / 2 + (y2 * ww) / 2);
              if (x2 & 1) {
                pixel = (pixel & 0x0f);
              } else {
                pixel = (pixel & 0xf0) >> 4;
              }
              if (pixel)
                drawRotateSprPixel(pixel, x, y, x1, y1, endx / 2, endy, c, s);
            }
          }
        } else {
          for (y1 = 0; y1 < h; y1++) {
            if (y1 + y >= -h && y1 + y < 128 + h) {
              for (x1 = 0; x1 < w; x1++) {
                if (x1 + x >= -w && x1 + x < 128 + w) {
                  pixel = readMem(adr + x1 + y1 * w);
                  if ((pixel & 0xf0) > 0)
                    drawRotateSprPixel(pixel >> 4, x, y, x1 * 2, y1, w, h / 2, c, s);
                  if ((pixel & 0x0f) > 0)
                    drawRotateSprPixel(pixel & 0xf, x, y, x1 * 2 + 1, y1, w, h / 2, c, s);
                }
              }
            }
          }
        }
      }
    }
  } else {
    i = 0;
    pixel = sprite_table[n].flags >> 4;
    if (!sprite_table[n].angle) {
      if (SPRITE_IS_FLIP_HORIZONTAL(n)) {
        if (sz != 1 << fixed_res_bit) {
          for (y1 = 0; y1 < ((h * sz) >> fixed_res_bit); y1++) {
            y2 = ((y1 << fixed_res_bit) + 1) / sz;
            if ((y + y1) > 128)
              return;
            for (x1 = 0; x1 < ((ww * sz) >> fixed_res_bit); x1++) {
              x2 = ((x1 << fixed_res_bit) + 1) / sz;
              ibit = readMem(adr + (x2 + y2 * ww) / 8);
              if (ibit & (1 << (7 - ((x2 + y2 * ww) & 7))))
                drawSprPixel(pixel, x, y, ww - x1, y1);
            }
          }
        } else {
          for (y1 = 0; y1 < h; y1++) {
            for (x1 = 0; x1 < ww; x1++) {
              if (i % 8 == 0) {
                ibit = readMem(adr);
                adr++;
              }
              if (ibit & 0x80)
                drawSprPixel(pixel, x, y, ww - x1, y1);
              ibit = ibit << 1;
              i++;
            }
          }
        }
      } else {
        if (sz != 1 << fixed_res_bit) {
          for (y1 = 0; y1 < ((h * sz) >> fixed_res_bit); y1++) {
            y2 = ((y1 << fixed_res_bit) + 1) / sz;
            if ((y + y1) > 128)
              return;
            for (x1 = 0; x1 < ((ww * sz) >> fixed_res_bit); x1++) {
              x2 = ((x1 << fixed_res_bit) + 1) / sz;
              ibit = readMem(adr + (x2 + y2 * ww) / 8);
              if (ibit & (1 << (7 - ((x2 + y2 * ww) & 7))))
                drawSprPixel(pixel, x, y, x1, y1);
            }
          }
        } else {
          for (y1 = 0; y1 < h; y1++) {
            for (x1 = 0; x1 < ww; x1++) {
              if (i % 8 == 0) {
                ibit = readMem(adr);
                adr++;
              }
              if (ibit & 0x80)
                drawSprPixel(pixel, x, y, x1, y1);
              ibit = ibit << 1;
              i++;
            }
          }
        }
      }
    } else {
      c = fixed_cos(sprite_table[n].angle);
      s = fixed_sin(sprite_table[n].angle);
      if (SPRITE_IS_FLIP_HORIZONTAL(n)) {
        if (sz != 1 << fixed_res_bit) {
          for (y1 = 0; y1 < ((h * sz) >> fixed_res_bit); y1++) {
            y2 = ((y1 << fixed_res_bit) + 1) / sz;
            if ((y + y1) > 128)
              return;
            for (x1 = 0; x1 < ((ww * sz) >> fixed_res_bit); x1++) {
              x2 = ((x1 << fixed_res_bit) + 1) / sz;
              ibit = readMem(adr + (x2 + y2 * ww) / 8);
              if (ibit & (1 << (7 - ((x2 + y2 * ww) & 7))))
                drawRotateSprPixel(pixel, x, y, ww - x1, y1, w, h / 2, c, s);
            }
          }
        } else {
          for (y1 = 0; y1 < h; y1++) {
            for (x1 = 0; x1 < ww; x1++) {
              if (i % 8 == 0) {
                ibit = readMem(adr);
                adr++;
              }
              if (ibit & 0x80)
                drawRotateSprPixel(pixel, x, y, ww - x1, y1, w, h / 2, c, s);
              ibit = ibit << 1;
              i++;
            }
          }
        }
      } else {
        if (sz != 1 << fixed_res_bit) {
          for (y1 = 0; y1 < ((h * sz) >> fixed_res_bit); y1++) {
            y2 = ((y1 << fixed_res_bit) + 1) / sz;
            if ((y + y1) > 128)
              return;
            for (x1 = 0; x1 < ((ww * sz) >> fixed_res_bit); x1++) {
              x2 = ((x1 << fixed_res_bit) + 1) / sz;
              ibit = readMem(adr + (x2 + y2 * ww) / 8);
              if (ibit & (1 << (7 - ((x2 + y2 * ww) & 7))))
                drawRotateSprPixel(pixel, x, y, x1, y1, w, h / 2, c, s);
            }
          }
        } else {
          for (y1 = 0; y1 < h; y1++) {
            for (x1 = 0; x1 < ww; x1++) {
              if (i % 8 == 0) {
                ibit = readMem(adr);
                adr++;
              }
              if (ibit & 0x80)
                drawRotateSprPixel(pixel, x, y, x1, y1, w, h / 2, c, s);
              ibit = ibit << 1;
              i++;
            }
          }
        }
      }
    }
  }
}

void drawImg(int16_t a, int16_t x, int16_t y, int16_t w, int16_t h) {
  if (!(imageSize <= 1 || imageSize == (1 << fixed_res_bit))) {
    drawImgS(a, x, y, w, h);
    return;
  }
  uint8_t p, color;
  for (int yi = 0; yi < h; yi++)
    for (int xi = 0; xi < w; xi++) {
      p = readMem(a);
      color = (p & 0xf0) >> 4;
      if (color > 0) {
        setPix(xi + x, yi + y, color);
      }
      xi++;
      color = p & 0x0f;
      if (color > 0) {
        setPix(xi + x, yi + y, color);
      }
      a++;
    }
}

void drawImgRLE(int16_t adr, int16_t x1, int16_t y1, int16_t w, int16_t h) {
  if (!(imageSize <= 1 || imageSize == (1 << fixed_res_bit))) {
    drawImgRLES(adr, x1, y1, w, h);
    return;
  }
  int16_t i = 0;
  uint8_t repeat = readMem(adr);
  adr++;
  int8_t color1 = (readMem(adr) & 0xf0) >> 4;
  int8_t color2 = readMem(adr) & 0xf;
  while (i < w * h) {
    if (repeat > 0x81) {
      if (color1 > 0) {
        setPix(x1 + i % w, y1 + i / w, color1);
      }
      if (color2 > 0) {
        setPix(x1 + i % w + 1, y1 + i / w, color2);
      }
      i += 2;
      adr++;
      repeat--;
      color1 = (readMem(adr) & 0xf0) >> 4;
      color2 = readMem(adr) & 0xf;
    } else if (repeat == 0x81) {
      repeat = readMem(adr);
      adr++;
      color1 = (readMem(adr) & 0xf0) >> 4;
      color2 = readMem(adr) & 0xf;
    } else if (repeat > 0) {
      if (color1 > 0) {
        setPix(x1 + i % w, y1 + i / w, color1);
      }
      if (color2 > 0) {
        setPix(x1 + i % w + 1, y1 + i / w, color2);
      }
      i += 2;
      repeat--;
    } else if (repeat == 0) {
      adr++;
      repeat = readMem(adr);
      adr++;
      color1 = (readMem(adr) & 0xf0) >> 4;
      color2 = readMem(adr) & 0xf;
    }
  }
}

void drawImageBit(int16_t adr, int16_t x1, int16_t y1, int16_t w, int16_t h) {
  if (!(imageSize <= 1 || imageSize == (1 << fixed_res_bit))) {
    drawImageBitS(adr, x1, y1, w, h);
    return;
  }
  int16_t i = 0;
  uint8_t ibit;
  for (int16_t y = 0; y < h; y++)
    for (int16_t x = 0; x < w; x++) {
      if (i % 8 == 0) {
        ibit = readMem(adr);
        adr++;
      }
      if (ibit & 0x80)
        setPix(x1 + x, y1 + y, color);
      else
        setPix(x1 + x, y1 + y, bgcolor);
      ibit = ibit << 1;
      i++;
    }
}

void drawImgS(int16_t a, int16_t x, int16_t y, int32_t w, int32_t h) {
  uint32_t p, x2, y2, color, s, endx;
  s = imageSize;
  endx = ((w * s) >> fixed_res_bit);
  for (int32_t yi = 0; yi < ((h * s) >> fixed_res_bit); yi++) {
    y2 = ((yi << fixed_res_bit) + 1) / s;
    if ((y + yi) > 128)
      return;
    for (int32_t xi = 0; xi < endx; xi++) {
      x2 = ((xi << fixed_res_bit) + 1) / s;
      if (x2 & 1) {
        p = readMem(a + x2 / 2 + (y2 * w) / 2);
        color = (p & 0x0f);
      } else {
        p = readMem(a + x2 / 2 + (y2 * w) / 2);
        color = (p & 0xf0) >> 4;
      }
      if (color)
        setPix(x + xi, y + yi, color);
    }
  }
}

void drawImgRLES(int16_t adr, int16_t x1, int16_t y1, int16_t w, int16_t h) {
  int16_t i = 0;
  uint8_t jx, jy;
  uint8_t repeat = readMem(adr);
  adr++;
  int8_t color1 = (readMem(adr) & 0xf0) >> 4;
  int8_t color2 = readMem(adr) & 0xf;
  uint8_t s = imageSize >> fixed_res_bit;
  while (i < w * h) {
    if (repeat > 0x81) {
      if (color1 > 0) {
        for (jx = 0; jx < s; jx++)
          for (jy = 0; jy < s; jy++)
            setPix(x1 + (i % w) * s + jx, y1 + i / w * s + jy, color1);
      }
      if (color2 > 0) {
        for (jx = 0; jx < s; jx++)
          for (jy = 0; jy < s; jy++)
            setPix(x1 + (i % w) * s + s + jx, y1 + i / w * s + jy, color2);
      }
      i += 2;
      adr++;
      repeat--;
      color1 = (readMem(adr) & 0xf0) >> 4;
      color2 = readMem(adr) & 0xf;
    } else if (repeat == 0x81) {
      repeat = readMem(adr);
      adr++;
      color1 = (readMem(adr) & 0xf0) >> 4;
      color2 = readMem(adr) & 0xf;
    } else if (repeat > 0) {
      if (color1 > 0) {
        for (jx = 0; jx < s; jx++)
          for (jy = 0; jy < s; jy++)
            setPix(x1 + (i % w) * s + jx, y1 + i / w * s + jy, color1);
      }
      if (color2 > 0) {
        for (jx = 0; jx < s; jx++)
          for (jy = 0; jy < s; jy++)
            setPix(x1 + (i % w) * s + s + jx, y1 + i / w * s + jy, color2);
      }
      i += 2;
      repeat--;
    } else if (repeat == 0) {
      adr++;
      repeat = readMem(adr);
      adr++;
      color1 = (readMem(adr) & 0xf0) >> 4;
      color2 = readMem(adr) & 0xf;
    }
  }
}

void drawImageBitS(int16_t a, int16_t x, int16_t y, int16_t w, int16_t h) {
  uint32_t p, x2, y2, s;
  s = imageSize;
  for (int32_t yi = 0; yi < ((h * s) >> fixed_res_bit); yi++) {
    y2 = ((yi << fixed_res_bit) + 1) / s;
    if ((y + yi) > 128)
      return;
    for (int32_t xi = 0; xi < ((w * s) >> fixed_res_bit); xi++) {
      x2 = ((xi << fixed_res_bit) + 1) / s;
      p = readMem(a + (x2 + y2 * w) / 8);
      if (p & (1 << (7 - ((x2 + y2 * w) & 7))))
        setPix(x + xi, y + yi, color);
      else
        setPix(x + xi, y + yi, bgcolor);
    }
  }
}

void loadTile(int16_t adr, uint8_t iwidth, uint8_t iheight, uint8_t width, uint8_t height) {
  tile.adr = adr;
  tile.imgwidth = iwidth;
  tile.imgheight = iheight;
  tile.width = width;
  tile.height = height;
  tile.pixwidth = width * iwidth;
  tile.pixheight = height * iheight;
}

void drawTile(int16_t x0, int16_t y0) {
  int x, y, nx, ny;
  uint16_t imgadr;
  tile.x = x0;
  tile.y = y0;
  for (x = 0; x < tile.width; x++) {
    nx = x0 + x * tile.imgwidth;
    for (y = 0; y < tile.height; y++) {
      ny = y0 + y * tile.imgheight;
      if (nx >= -tile.width && nx < 128 && ny >= -tile.height && ny < 128) {
        imgadr = readInt(tile.adr + (x + y * tile.width) * 2);
        if (imgadr > 0)
          drawImg(imgadr, nx, ny, tile.imgwidth, tile.imgheight);
      }
    }
  }
}

inline void drawFVLine(int x, int y1, int y2) {
  for (int i = y1; i <= y2; i++)
    setPix(x, i, color);
}

void drawFHLine(int16_t x1, int16_t x2, uint16_t y) {
  uint8_t *nPtr, c;
  uint16_t i;
  if (isClip) {
    if (y < clipy0 || y >= clipy1)
      return;
    if (x1 < clipx0)
      x1 = clipx0;
    if (x2 >= clipx1)
      x2 = clipx1;
  } else {
    if (y > 127)
      return;
    if (x1 < 0)
      x1 = 0;
    if (x2 >= 127)
      x2 = 127;
  }
  if (x1 & 1) {
    screen[SCREEN_ADDR(x1 / 2, y)] = (screen[SCREEN_ADDR(x1 / 2, y)] & 0xf0) + color;
    x1++;
  }
  if (!(x2 & 1)) {
    screen[SCREEN_ADDR(x2 / 2, y)] = (screen[SCREEN_ADDR(x2 / 2, y)] & 0x0f) + (color << 4);
    x2--;
  }
  SET_LINE_IS_DRAW(y);
  i = x1 / 2;
  c = (color << 4) + color;
  nPtr = (uint8_t *)&screen[SCREEN_ADDR(i, y)];
  for (; i <= x2 / 2; i++)
    *nPtr++ = c;
}

void drwLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  if (x1 == x2) {
    if (y1 > y2)
      drawFVLine(x1, y2, y1);
    else
      drawFVLine(x1, y1, y2);
    return;
  } else if (y1 == y2) {
    if (x1 > x2)
      drawFHLine(x2, x1, y1);
    else
      drawFHLine(x1, x2, y1);
    return;
  }
  int deltaX = abs(x2 - x1);
  int deltaY = abs(y2 - y1);
  int signX = x1 < x2 ? 1 : -1;
  int signY = y1 < y2 ? 1 : -1;
  int error = deltaX - deltaY;
  int error2;
  setPix(x2, y2, color);
  while (x1 != x2 || y1 != y2) {
    setPix(x1, y1, color);
    error2 = error * 2;
    if (error2 > -deltaY) {
      error -= deltaY;
      x1 += signX;
    }
    if (error2 < deltaX) {
      error += deltaX;
      y1 += signY;
    }
  }
}

void setClip(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  clipx0 = (x0 >= 0 && x0 < 127) ? x0 : 0;
  clipy0 = (y0 >= 0 && y0 < 127) ? y0 : 0;
  clipx1 = (x0 + x1 > 0 && x0 + x1 <= 127) ? x0 + x1 : 128;
  clipy1 = (y0 + y1 > 0 && y0 + y1 <= 127) ? y0 + y1 : 128;
  if (clipx0 == 0 && clipy0 == 0 && clipx1 == 128 && clipy1 == 128)
    isClip = 0;
  else
    isClip = 1;
}

inline void setPix(uint16_t x, uint16_t y, uint8_t c) {
  uint16_t xi, b, n;
  if (isClip) {
    if (x < clipx1 && x >= clipx0 && y < clipy1 && y >= clipy0) {
      xi = x >> 1;
      b = screen[SCREEN_ADDR(xi, y)];
      if (x & 1)
        n = (b & 0xf0) + c;
      else
        n = (b & 0x0f) + (c << 4);
      if (b != n) {
        SET_LINE_IS_DRAW(y);
        screen[SCREEN_ADDR(xi, y)] = n;
      }
    }
  } else {
    if (x < 128 && y < 128) {
      xi = x >> 1;
      b = screen[SCREEN_ADDR(xi, y)];
      if (x & 1)
        n = (b & 0xf0) + c;
      else
        n = (b & 0x0f) + (c << 4);
      if (b != n) {
        SET_LINE_IS_DRAW(y);
        screen[SCREEN_ADDR(xi, y)] = n;
      }
    }
  }
}

uint8_t getPix(uint8_t x, uint8_t y) {
  uint16_t xi, b;
  if (x < 128 && y < 128) {
    xi = x / 2;
    if (x % 2)
      b = (screen[SCREEN_ADDR(xi, y)] & 0x0f);
    else
      b = (screen[SCREEN_ADDR(xi, y)] & 0xf0) >> 4;
    return b;
  }
  return 0;
}

void changePalette(uint8_t n, uint16_t c) {
  if (n < 16) {
    palette[n] = c;
    for (uint8_t y = 0; y < 128; y++) {
      for (uint8_t x = 0; x < 64; x++) {
        if (((screen[SCREEN_ADDR(x, y)] & 0xf0) >> 4) == n || (screen[SCREEN_ADDR(x, y)] & 0x0f) == n)
          SET_LINE_IS_DRAW(y);
      }
    }
  } else if (n < 32)
    sprtpalette[n - 16] = c;
}

void scrollScreen(uint8_t step, uint8_t direction) {
  uint8_t bufPixel;
  if (direction == 2) {
    for (uint8_t y = clipy0; y < clipy1; y++) {
      bufPixel = screen[SCREEN_ADDR(clipx0 / 2, y)];
      for (uint8_t x = clipx0 / 2 + 1; x < clipx1 / 2; x++) {
        if (screen[SCREEN_ADDR(x - 1, y)] != screen[SCREEN_ADDR(x, y)])
          SET_LINE_IS_DRAW(y);
        screen[SCREEN_ADDR(x - 1, y)] = screen[SCREEN_ADDR(x, y)];
      }
      if (screen[SCREEN_ADDR((clipx1 - 1) / 2, y)] != bufPixel)
        SET_LINE_IS_DRAW(y);
      screen[SCREEN_ADDR((clipx1 - 1) / 2, y)] = bufPixel;
    }
    for (uint8_t n = 0; n < 32; n++)
      if (SPRITE_IS_SCROLLED(n) && !isClip) {
        sprite_table[n].x -= 8;
        sprite_table[n].previousx -= 8;
      }
  } else if (direction == 1) {
    for (uint8_t x = clipx0 / 2; x < clipx1 / 2; x++) {
      bufPixel = screen[SCREEN_ADDR(x, clipy0)];
      for (uint8_t y = clipy0 + 1; y < clipy1; y++) {
        if (screen[SCREEN_ADDR(x, y - 1)] != screen[SCREEN_ADDR(x, y)])
          SET_LINE_IS_DRAW(y);
        screen[SCREEN_ADDR(x, y - 1)] = screen[SCREEN_ADDR(x, y)];
      }
      if (screen[SCREEN_ADDR(x, clipy1 - 1)] != bufPixel)
        SET_LINE_IS_DRAW(clipy1 - 1);
      screen[SCREEN_ADDR(x, clipy1 - 1)] = bufPixel;
    }
    for (uint8_t n = 0; n < 32; n++)
      if (SPRITE_IS_SCROLLED(n) && !isClip) {
        sprite_table[n].y -= 4;
        sprite_table[n].previousy -= 4;
      }
  } else if (direction == 0) {
    for (uint8_t y = clipy0; y < clipy1; y++) {
      bufPixel = screen[SCREEN_ADDR((clipx1 - 1) / 2, y)];
      for (uint8_t x = (clipx1 - 1) / 2; x > clipx0 / 2; x--) {
        if (screen[SCREEN_ADDR(x, y)] != screen[SCREEN_ADDR(x - 1, y)])
          SET_LINE_IS_DRAW(y);
        screen[SCREEN_ADDR(x, y)] = screen[SCREEN_ADDR(x - 1, y)];
      }
      if (screen[SCREEN_ADDR(clipx0 / 2, y)] != bufPixel)
        SET_LINE_IS_DRAW(y);
      screen[SCREEN_ADDR(clipx0 / 2, y)] = bufPixel;
    }
    for (uint8_t n = 0; n < 32; n++)
      if (SPRITE_IS_SCROLLED(n) && !isClip) {
        sprite_table[n].x += 8;
        sprite_table[n].previousx += 8;
      }
  } else {
    for (uint8_t x = clipx0 / 2; x < clipx1 / 2; x++) {
      bufPixel = screen[SCREEN_ADDR(x, (clipx1 - 1) / 2)];
      for (uint8_t y = clipy1 - 1; y > clipy0; y--) {
        if (screen[SCREEN_ADDR(x, y)] != screen[SCREEN_ADDR(x, y - 1)])
          SET_LINE_IS_DRAW(y);
        screen[SCREEN_ADDR(x, y)] = screen[SCREEN_ADDR(x, y - 1)];
      }
      if (screen[SCREEN_ADDR(x, clipy0)] != bufPixel)
        SET_LINE_IS_DRAW(0);
      screen[SCREEN_ADDR(x, clipy0)] = bufPixel;
    }
    for (uint8_t n = 0; n < 32; n++)
      if (SPRITE_IS_SCROLLED(n) && !isClip) {
        sprite_table[n].y += 4;
        sprite_table[n].previousy += 4;
      }
  }
  if (tile.adr > 0 && !isClip)
    tileDrawLine(step, direction);
}

void tileDrawLine(uint8_t step, uint8_t direction) {
  int16_t x, y, x0, y0, y1, nx, ny;
  uint16_t imgadr;
  if (direction == 2) {
    tile.x -= step * 2;
    x0 = tile.x;
    y0 = tile.y;
    x = (127 - x0) / tile.imgwidth;
    nx = x0 + x * tile.imgwidth;
    if (x < tile.width && x >= -tile.width) {
      for (y = 0; y < tile.height; y++) {
        ny = y0 + y * tile.imgheight;
        if (ny > -tile.height && ny < 128) {
          imgadr = readInt(tile.adr + (x + y * tile.width) * 2);
          if (imgadr > 0)
            drawImg(imgadr, nx, ny, tile.imgwidth, tile.imgheight);
          else
            fillRect(nx, ny, tile.imgwidth, tile.imgheight, bgcolor);
        }
      }
    } else if (tile.width * tile.imgwidth + x0 >= 0) {
      y0 = (y0 > 0) ? y0 : 0;
      y1 = (tile.y + tile.height * tile.imgheight < 128) ? tile.y + tile.height * tile.imgheight - y0 : 127 - y0;
      if (y0 < 127 && y1 > 0)
        fillRect(127 - step * 2, y0, step * 2, y1, bgcolor);
    }
  } else if (direction == 1) {
    tile.y -= step;
    x0 = tile.x;
    y0 = tile.y;
    y = (127 - y0) / tile.imgheight;
    ny = y0 + y * tile.imgheight;
    if (y < tile.height && y >= -tile.height)
      for (x = 0; x < tile.width; x++) {
        nx = x0 + x * tile.imgwidth;
        if (nx > -tile.width && nx < 128) {
          imgadr = readInt(tile.adr + (x + y * tile.width) * 2);
          if (imgadr > 0)
            drawImg(imgadr, nx, ny, tile.imgwidth, tile.imgheight);
          else
            fillRect(nx, ny, tile.imgwidth, tile.imgheight, bgcolor);
        }
      }
  } else if (direction == 0) {
    tile.x += step * 2;
    x0 = tile.x;
    y0 = tile.y;
    x = (0 - x0) / tile.imgwidth;
    nx = x0 + x * tile.imgwidth;
    if (x0 < 0 && x >= -tile.width) {
      for (y = 0; y < tile.height; y++) {
        ny = y0 + y * tile.imgheight;
        if (ny > -tile.height && ny < 128) {
          imgadr = readInt(tile.adr + (x + y * tile.width) * 2);
          if (imgadr > 0)
            drawImg(imgadr, nx, ny, tile.imgwidth, tile.imgheight);
          else
            fillRect(nx, ny, tile.imgwidth, tile.imgheight, bgcolor);
        }
      }
    } else if (x0 < 128) {
      y0 = (y0 > 0) ? y0 : 0;
      y1 = (tile.y + tile.height * tile.imgheight < 128) ? tile.y + tile.height * tile.imgheight - y0 : 127 - y0;
      if (y0 < 127 && y1 > 0)
        fillRect(0, y0, step * 2, y1, bgcolor);
    }
  } else if (direction == 3) {
    tile.y += step;
    x0 = tile.x;
    y0 = tile.y;
    y = (0 - y0) / tile.imgheight;
    ny = y0 + y * tile.imgheight;
    if (y0 < 0 && y >= -tile.height)
      for (x = 0; x < tile.width; x++) {
        nx = x0 + x * tile.imgwidth;
        if (nx > -tile.width && nx < 128) {
          imgadr = readInt(tile.adr + (x + y * tile.width) * 2);
          if (imgadr > 0)
            drawImg(imgadr, nx, ny, tile.imgwidth, tile.imgheight);
          else
            fillRect(nx, ny, tile.imgwidth, tile.imgheight, bgcolor);
        }
      }
  }
}

void charLineUp(uint8_t n) {
  clearScr(bgcolor);
  for (uint16_t i = 0; i < 336 - n * 21; i++) {
    charArray[i] = charArray[i + n * 21];
    putchar(charArray[i], (i % 21) * 6, (i / 21) * 8);
  }
}

inline void setCharX(int8_t x) {
  regx = x;
}

inline void setCharY(int8_t y) {
  regy = y;
}

inline int8_t getCharY() {
  return regy;
}

void printc(char c, uint8_t fc, uint8_t bc) {
  if (regy > 15) {
    regy = 15;
    charLineUp(1);
  }
  if (c == '\n') {
    fillRect(regx * 6, regy * 8, 127 - regx * 6, 8, bgcolor);
    for (uint8_t i = regx; i <= 21; i++) {
      charArray[regx + regy * 21] = ' ';
    }
    regy++;
    regx = 0;
  } else if (c == '\t') {
    for (uint8_t i = 0; i <= regx % 5; i++) {
      fillRect(regx * 6, regy * 8, 6, 8, bgcolor);
      charArray[regx + regy * 21] = ' ';
      regx++;
      if (regx > 20) {
        regy++;
        regx = 0;
      }
    }
  } else {
    fillRect(regx * 6, regy * 8, 6, 8, bgcolor);
    putchar(c, regx * 6, regy * 8);
    charArray[regx + regy * 21] = c;
    regx++;
    if (regx > 20) {
      regy++;
      regx = 0;
    }
  }
}


void printfix(int16_t value, uint8_t fc, uint8_t bc) {
  char sbuffer[10];
  const uint16_t fractPartMask = (1 << fixed_res_bit) - 1;
  int16_t j;
  if (value == 0) {
    printc('0', color, bgcolor);
  }
  if (value < 0) {
    printc('-', color, bgcolor);
    value = (~value) + 1;
  }
  int16_t intPart = value >> fixed_res_bit;
  value &= fractPartMask;

  // преобразуем целую часть
  itoa(intPart, sbuffer, 10);
  j = 0;
  while (sbuffer[j]) {
    printc(sbuffer[j], color, bgcolor);
    j++;
  }
  char *ptr = sbuffer;
  // если есть дробная часть
  if (value != 0) {
    *ptr = '.';
    for (j = 0; j < 3; j++) {
      value &= fractPartMask;
      value *= 10;
      //value <<= 1;
      //value += value << 2;
      *++ptr = (uint8_t)(value >> fixed_res_bit) + '0';
    }
    // удаляем завершаюшие нули
    while (ptr[0] == '0') --ptr;
    ptr[1] = 0;
  }
  j = 0;
  while (sbuffer[j]) {
    printc(sbuffer[j], color, bgcolor);
    j++;
  }
}

inline void setColor(uint8_t c) {
  color = c & 0xf;
}

inline void setBgColor(uint8_t c) {
  bgcolor = c & 0xf;
}

void drwRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  drawFHLine(x0, x1, y0);
  drawFHLine(x0, x1, y1);
  drawFVLine(x0, y0, y1);
  drawFVLine(x1, y0, y1);
}

void fillRect(int8_t x, int8_t y, uint8_t w, uint8_t h, uint8_t c) {
  for (int16_t jx = x; jx < x + w; jx++)
    for (int16_t jy = y; jy < y + h; jy++)
      setPix(jx, jy, c);
}

void fllRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
  for (int16_t jy = y0; jy <= y1; jy++)
    drawFHLine(x0, x1, jy);
}

void drwCirc(int16_t x0, int16_t y0, int16_t r) {
  int16_t x = 0;
  int16_t dx = 1;
  int16_t dy = r + r;
  int16_t p = -(r >> 1);

  // These are ordered to minimise coordinate changes in x or y
  // drawPixel can then send fewer bounding box commands
  setPix(x0 + r, y0, color);
  setPix(x0 - r, y0, color);
  setPix(x0, y0 - r, color);
  setPix(x0, y0 + r, color);

  while (x < r) {

    if (p >= 0) {
      dy -= 2;
      p -= dy;
      r--;
    }

    dx += 2;
    p += dx;

    x++;

    // These are ordered to minimise coordinate changes in x or y
    // drawPixel can then send fewer bounding box commands
    setPix(x0 + x, y0 + r, color);
    setPix(x0 - x, y0 + r, color);
    setPix(x0 - x, y0 - r, color);
    setPix(x0 + x, y0 - r, color);

    setPix(x0 + r, y0 + x, color);
    setPix(x0 - r, y0 + x, color);
    setPix(x0 - r, y0 - x, color);
    setPix(x0 + r, y0 - x, color);
  }
}

void fllCirc(int16_t x0, int16_t y0, int16_t r) {
  int16_t x = 0;
  int16_t dx = 1;
  int16_t dy = r + r;
  int16_t p = -(r >> 1);

  drawFHLine(x0 - r, x0 + r, y0);

  while (x < r) {
    if (p >= 0) {
      dy -= 2;
      p -= dy;
      r--;
    }

    dx += 2;
    p += dx;

    x++;

    drawFHLine(x0 - r, x0 + r, y0 + x);
    drawFHLine(x0 - r, x0 + r, y0 - x);
    drawFHLine(x0 - x, x0 + x, y0 + r);
    drawFHLine(x0 - x, x0 + x, y0 - r);
  }
}

void drwTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3) {
  drwLine(x1, y1, x2, y2);
  drwLine(x2, y2, x3, y3);
  drwLine(x3, y3, x1, y1);
}

void fllTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
  int32_t a, b, y, last, t;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    t = y0;
    y0 = y1;
    y1 = t;
    t = x0;
    x0 = x1;
    x1 = t;
  }
  if (y1 > y2) {
    t = y2;
    y2 = y1;
    y1 = t;
    t = x2;
    x2 = x1;
    x1 = t;
  }
  if (y0 > y1) {
    t = y0;
    y0 = y1;
    y1 = t;
    t = x0;
    x0 = x1;
    x1 = t;
  }

  if (y0 == y2) {
    a = b = x0;
    if (x1 < a)
      a = x1;
    else if (x1 > b)
      b = x1;
    if (x2 < a)
      a = x2;
    else if (x2 > b)
      b = x2;
    drawFHLine(a, b, y0);
    return;
  }

  int32_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa = 0,
    sb = 0;

  if (y1 == y2)
    last = y1;
  else
    last = y1 - 1;

  for (y = y0; y <= last; y++) {
    a = x0 + sa / dy01;
    b = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;

    if (a > b) {
      t = a;
      a = b;
      b = t;
    }
    drawFHLine(a, b, y);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for (; y <= y2; y++) {
    a = x1 + sa / dy12;
    b = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;

    if (a > b) {
      t = a;
      a = b;
      b = t;
    }
    drawFHLine(a, b, y);
  }
}

void putString(char s[], int8_t y) {
  int8_t i = 0;
  while (s[i] != 0 && i < 32) {
    if (s[i] != '/') {
      if (i < 17)
        putchar(s[i], 25 + i * 6, y);
      else
        putchar(s[i], 25 + (i - 17) * 6, y + 8);
    }
    i++;
    if (s[i] == '.')
      return;
  }
}

void putchar(char c, uint8_t x, uint8_t y) {
  for (int8_t i = 0; i < 5; i++) {  // Char bitmap = 5 columns
    uint8_t line = pgm_read_byte(&font_a[c * 5 + i]);
    for (int8_t j = 0; j < 8; j++, line >>= 1) {
      if (line & 1)
        setPix(x + i, y + j, color);
    }
  }
}

void drawChar(uint8_t c, uint16_t x, uint16_t y) {
  if (custom_font.address == 0) {
    for (int8_t i = 0; i < 5; i++) {  // Char bitmap = 5 columns
      int16_t line = pgm_read_byte(&font_a[c * 5 + i]);
      for (int8_t j = 0; j < 8; j++, line >>= 1) {
        if (line & 1)
          setPix(x + i, y + j, color);
      }
    }
  } else if (c <= custom_font.end) {
    if (c < custom_font.start)
      return;
    c -= custom_font.start;
    int16_t pos = (c % custom_font.columns) * custom_font.charwidth + (c / custom_font.columns) * (custom_font.charheight * custom_font.imgwidth);
    for (int8_t j = 0; j < custom_font.charheight; j++) {
      for (int8_t i = 0; i < custom_font.charwidth; i++) {
        int8_t line = readMem(custom_font.address + (pos + i) / 8);
        if (line & (1 << (7 - ((pos + i) & 7))))
          setPix(x + i, y + j, color);
      }
      pos += custom_font.imgwidth;
    }
  }
}

void drawString(uint16_t s, uint16_t x, uint16_t y) {
  int16_t i = 0, nx = x;
  uint8_t c;
  c = readMem(s + i);
  while (c) {
    if (c == 10) {
      nx = x - custom_font.charwidth;
      ;
      y += custom_font.charheight;
    } else if (nx > -custom_font.charwidth && nx < 128)
      drawChar(readMem(s + i), nx, y);
    i++;
    c = readMem(s + i);
    nx += custom_font.charwidth;
  }
}

void fontload(int16_t adr, int8_t start, int8_t end) {
  custom_font.address = adr;
  custom_font.start = start & 0xff;
  custom_font.end = end & 0xff;
}

void fontsize(int16_t imgwidth, int16_t imgheight, int16_t charwidth, int16_t charheight) {
  custom_font.imgwidth = imgwidth;
  custom_font.imgheight = imgheight;
  custom_font.charwidth = charwidth & 0xff;
  custom_font.charheight = charheight & 0xff;
  custom_font.columns = custom_font.imgwidth / custom_font.charwidth;
}
