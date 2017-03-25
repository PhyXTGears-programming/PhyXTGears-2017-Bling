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

bool serialInterp () {
  //  if (noSerial) {
  //    Serial.println("Serial is disabled");
  //    return false;
  //  }
  while (Serial.available() > 0) {
    Serial.readString();
  }
  Serial.println("What would you like to do?");
  Serial.println("\ttest");
  Serial.println("\tbling");
  Serial.println("\tteam");
  String in = serialIn();
  Serial.println(in);
  in.toUpperCase();
  if (in == "TEST" || in == "TEST\n") {
    if (serialBool("Would you like to enter test mode? ")) {
      testing = true;
      return true;
    } else {
      return false;
    }
  } else if (in == "BLING" || in == "BLING\n") {
    if (serialBool("Would you like to enable bling? ")) {
      testing = false;
      return true;
    } else {
      return false;
    }
  } else if (in == "TEAM" || in == "TEAM\n") {
    Serial.print("Team Slot Number: ");
    int teamS = Serial.parseInt();
    Serial.println(teamS);
    if (serialBool("Would you like to enable bling? ")) {
      testing = false;
      return true;
    } else {
      return false;
    }
  }
}

/*
    else if (in == "DISABLE" || in == "DISABLE\n") {
    if (serialBool("Would you like to disable Serial? ")) {
      noSerial = true;
      return true;
    } else {
      return false;
    }
*/

bool serialBool (String message) {
  Serial.print(message);
  String in = serialIn();
  Serial.println(in);
  in.toUpperCase();
  if (in == "Y" || in == "YES") {
    Serial.println("Yes");
    return true;
  } else {
    Serial.println("No");
    return false;
  }
}

String serialIn () {
  while (Serial.available() < 1) {}
  return Serial.readString();
}

