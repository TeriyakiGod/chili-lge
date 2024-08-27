#include <io.h>
#include <esp_lge.h>
// Serial communication
int16_t serialBegin()
{
  serial_used = 1;
  return 1;
}

int16_t serialAvailable()
{
  if (Serial.available() && serial_used)
    return 1;
  return 0;
}

int16_t serialRead()
{
  if (Serial.available() && serial_used)
    return Serial.read();
  return 0;
}

int16_t serialWrite(int16_t n)
{
  Serial.write((char)n);
  return 1;
}

// Digital I/O

// These are the pins for ESP8266 boards
//      Name   GPIO    NodeMCU      Function
#define PIN_D0  16  // GPIO16       WAKE
#define PIN_D1   5  // GPIO5        User purpose
#define PIN_D2   4  // GPIO4        User purpose
#define PIN_D3   0  // GPIO0        Low on boot means enter FLASH mode
#define PIN_D4   2  // GPIO2        TXD1 (must be high on boot to go to UART0 FLASH mode)
#define PIN_D5  14  // GPIO14       HSCLK
#define PIN_D6  12  // GPIO12       HMISO
#define PIN_D7  13  // GPIO13       HMOSI  RXD2
#define PIN_D8  15  // GPIO15       HCS    TXD0 (must be low on boot to enter UART0 FLASH mode)
#define PIN_D9   3  //              RXD0
#define PIN_D10  1  //              TXD0

#define PIN_MOSI 8  // SD1          FLASH and overlap mode
#define PIN_MISO 7  // SD0
#define PIN_SCLK 6  // CLK
#define PIN_HWCS 0  // D3

#define PIN_D11  9  // SD2
#define PIN_D12 10  // SD4

// Button codes //might be fucked up idk
#define BTN_UP 1
#define BTN_DOWN 2
#define BTN_LEFT 4
#define BTN_RIGHT 8
#define BTN_A 16
#define BTN_SELECT 32
#define BTN_B 64
#define BTN_START 128

void getKey()
{
  thiskey = 0;
  if (digitalRead(PIN_D1) == LOW)
    thiskey |= BTN_DOWN;
  if (digitalRead(PIN_D2) == LOW)
    thiskey |= BTN_A;
}

void keyboardInit()
{
  pinMode(PIN_D1, INPUT_PULLUP);
  pinMode(PIN_D2, INPUT_PULLUP);
  pinMode(PIN_D3, OUTPUT); // SOUNDPIN
}
