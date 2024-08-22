#define JALAPENO
#define RAM_SIZE    20 * 1024
#define FREQUENCY   160
#define APPSK  "87654321"
#define BUILD_VERSION "esp-lge v1.2.0"
#define APSSID "JALAPENO"
#define APHOST "jalapeno"
#define SOUNDPIN            5 // PIN D1
#define DEBUG_ON_SCREEN
#define SCREEN_REAL_WIDTH   128
#define SCREEN_REAL_HEIGHT  128
#define SCREEN_ROTATION 0 // Rotates screen by degrees 0 - 0; 1 - 90; 2 - 180; 3 - 270;

#define SCREEN_WIDTH        128
#define SCREEN_WIDTH_BYTES  64
#define SCREEN_HEIGHT       128
#define SCREEN_SIZE (SCREEN_HEIGHT * SCREEN_WIDTH_BYTES)
#define SCREEN_ARRAY_DEF SCREEN_SIZE
#define SCREEN_ADDR(x, y) ((int(y) << 6) + int(x))

#define MULTIPLY_FP_RESOLUTION_BITS  8
#define PARTICLE_COUNT  32
#define SPRITE_COUNT    32
#define EEPROM_SIZE     512
