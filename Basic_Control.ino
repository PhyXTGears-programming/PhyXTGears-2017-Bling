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
  matrix.fillScreen(matrix.Color(0, 0, 0));
}

void updateScreen() {
  brightnessControl();
  matrix.show();
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
// 255, 255, 150
void runBling (int order[]) {
  int n = ceil(sizeof(blingPrograms) / sizeof(int));
  Serial.println("N: " + String(n));
  Serial.println(sizeof(blingPrograms));
  Serial.println(sizeof(int));
  int co[] = {0, 150, 0};
  int co2[] = {150, 150, 150};
  for (int i = 0; i < n; i++) {
    Serial.println("Running #" + String(i + 1) + ": " + String(blingPrograms[i]));
    switch (blingPrograms[i]) {
      case 0:
        rDraw(800, matrix.Color(0, 255, 255), 9, 0, true);
        theaterChase(5, 0, matrix.Color(255, 0, 0), true);
        Reset();
        break;
      case 1:
        for (int j = 0; j < 9; j++) {
          rectangleZoom(0, 0, 40, 16, matrix.Color(0, 25, 112), 9, true);
          Reset();
        }
        break;
      case 2:
        printText("I'm Spitfire", co, 50, true, true, 1);
        Reset();
        break;
      case 3:
        //        matrix.fillScreen(matrix.Color(255, 255, 150));
        //        updateScreen();
        //        delay(250);
        //        Reset();
        break;
      case 4:
        zigZag(2000, matrix.Color(0, 0, 255), matrix.Color(255, 0, 0), 100, 5);
        Reset();
        break;
      case 5:
        brightOver(255);
        strobePixel(2500, 0, matrix.Color(0, 0, 0), 5, true);
        Reset();
        break;
      case 6:
        brightOver(255);
        strobePixel(1500, 0, matrix.Color(255, 255, 255), 1, false);
        Reset();
        break;
      case 7:
        sinWave(matrix.Color(random(255), random(255), random(255)), 9, 3, float(0.2));
        delay(1000);
        Reset();
        break;
      case 8:
        screenSaver(4500, 7, 6, 7, 50);
        Reset();
        printText("First", co2, 21);
        Reset();
        break;
      case 9:
        spot(7000, 5, 10, true);
        Reset();
        break;
    }
    Serial.print("d");
    Reset();
    Serial.println("one");
  }
}

void Reset () {
  clearScreen();
  updateScreen();
  progBright = false;
}

void setupPins () {
  pinMode(gearSensePin, INPUT_PULLUP);
  //  attachInterrupt(digitalPinToInterrupt(gearSensePin), pixelAlert, FALLING);
}

void brightOver (int b) {
  progBright = true;
  bright = b;
}