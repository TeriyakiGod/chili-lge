// IO functions for the Arduino

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

// Define NODEMCU v3 pins
// #define PIN_D0 16
#define PIN_D1 5
#define PIN_D2 4
#define PIN_D3 0

// Define button codes
#define BTN_UP 1
#define BTN_DOWN 2
#define BTN_LEFT 4
#define BTN_RIGHT 8
#define BTN_SELECT 16
#define BTN_A 32
#define BTN_B 64
#define BTN_START 128

void keyboardInit() {
  pinMode(PIN_D1, INPUT_PULLUP);
  pinMode(PIN_D2, INPUT_PULLUP);
  pinMode(PIN_D3, OUTPUT);  //SOUNDPIN
}

// Digital I/O
void getKey() {
  thiskey = 0;
  if (digitalRead(PIN_D1) == LOW)
    thiskey |= BTN_DOWN;
  if (digitalRead(PIN_D2) == LOW)
    thiskey |= BTN_START;
}
