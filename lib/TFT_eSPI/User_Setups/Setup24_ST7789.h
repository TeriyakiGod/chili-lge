#define ST7735_DRIVER
#define TFT_WIDTH  128
#define TFT_HEIGHT 128
//#define ST7735_INITB
//#define ST7735_GREENTAB
//#define ST7735_GREENTAB2
#define ST7735_GREENTAB3
//#define ST7735_GREENTAB128
//#define ST7735_REDTAB
//#define ST7735_BLACKTAB
#define LOAD_GLCD
#define SPI_FREQUENCY  27000000
#define TFT_CS     PIN_D2
#define TFT_RST    PIN_D1  // Reset pin
#define TFT_DC     PIN_D3  // Data/Command pin (AO)
#define TFT_MOSI   PIN_D7  // SDM pin (MOSI)
#define TFT_SCLK   PIN_D5  // SCK pin