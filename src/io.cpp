#include "io.h"
#include "esp_lge.h"
//Serial communication
int16_t serialBegin() {
  serial_used = 1;
  return 1;
}

int16_t serialAvailable() {
  if (Serial.available() && serial_used)
    return 1;
  return 0;
}

int16_t serialRead() {
  if (Serial.available() && serial_used)
    return Serial.read();
  return 0;
}

int16_t serialWrite(int16_t n) {
  Serial.write((char)n);
  return 1;
}

// Digital I/O
void getKey() {
  thiskey = 0;
  if (digitalRead(PIN_D1) == LOW)
    thiskey |= BTN_DOWN;
  if (digitalRead(PIN_D2) == LOW)
    thiskey |= BTN_SELECT;
}

void keyboardInit() {
  pinMode(PIN_D1, INPUT_PULLUP);
  pinMode(PIN_D2, INPUT_PULLUP);
  pinMode(PIN_D3, OUTPUT);  //SOUNDPIN
}
