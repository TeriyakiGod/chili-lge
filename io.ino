// IO functions for the Arduino

//Serial communication
int16_t serialBegin(){
  serial_used = 1;
  return 1;
}

int16_t serialAvailable(){
  if(Serial.available() && serial_used)
    return 1;
  return 0;
}

int16_t serialRead(){
  if(Serial.available() && serial_used)
    return Serial.read();
  return 0;
}

int16_t serialWrite(int16_t n){
  Serial.write((char) n);
  return 1;
}

// Define NODEMCU v3 pins
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
#define D9 3 //(RX)
#define D10 1 //(TX)


// Define button codes
#define BTN_UP 1
#define BTN_DOWN 2
#define BTN_LEFT 4
#define BTN_RIGHT 8
#define BTN_SELECT 16
#define BTN_A 32
#define BTN_B 64
#define BTN_START 128
void keyboardInit(){
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D8, INPUT);
  pinMode(D9, INPUT);
  pinMode(D10, INPUT);
}
// Digital I/O
void getKey(){
    thiskey = 0;
    if(digitalRead(D0) == HIGH)
        thiskey = thiskey | BTN_UP;
    if(digitalRead(D1) == HIGH)
        thiskey = thiskey | BTN_DOWN;
    if(digitalRead(D2) == HIGH) 
        thiskey = thiskey | BTN_LEFT;
    if(digitalRead(D3) == HIGH)  
        thiskey = thiskey | BTN_RIGHT;
    if(digitalRead(D4) == HIGH)
        thiskey = thiskey | BTN_SELECT;
    if(digitalRead(D8) == HIGH)
        thiskey = thiskey | BTN_A;
    if(digitalRead(D9) == HIGH)
        thiskey = thiskey | BTN_B;
    if(digitalRead(D10) == HIGH)
        thiskey = thiskey | BTN_START;

}