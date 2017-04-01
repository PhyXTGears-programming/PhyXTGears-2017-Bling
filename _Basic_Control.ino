void brightnessControl() {
  float sensorValue = analogRead(potentiometerPIN) / 8.6f;
  if (sensorValue > 107) {
    sensorValue = 107;
  }
  if (OVER) {
    sensorValue = BRIGHT;
  }
  if (progBright) {
    sensorValue = bright;
  }
  //  Serial.println(int(sensorValue));
  matrix.setBrightness(int(sensorValue));
  gearString.setBrightness(int(sensorValue));
}

void clearScreen() {
  matrix.fillScreen(BLACK);
}

void updateScreen() {
  brightnessControl();
  matrix.show();
  if (Serial.available() > 0) {
    roboRioSerial();
  }
}

uint16_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void Reset () {
  clearScreen();
  updateScreen();
  progBright = false;
  //  matrix.setFont(&FONT);
}

void setupPins () {
  pinMode(gearSensePin, INPUT_PULLUP);
  //  attachInterrupt(digitalPinToInterrupt(gearSensePin), pixelAlert, FALLING);
}

void brightOver (int b) {
  progBright = true;
  bright = b;
}
