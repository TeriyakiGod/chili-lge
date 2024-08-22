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

// Digital I/O
void getKey(){
    thiskey = 0;
    if (digitalRead(2) == HIGH) thiskey |= 4;   // LEFT (D4 -> GPIO2)
    if (digitalRead(0) == HIGH) thiskey |= 8;   // RIGHT (D3 -> GPIO0)
    if (digitalRead(4) == HIGH) thiskey |= 16;  // OK (D2 -> GPIO4)
    //TODO: add support for other buttons
  
}