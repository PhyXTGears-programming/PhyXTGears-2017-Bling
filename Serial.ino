void roboRioSerial() {
  String rI = serialIn(1);
  rI.toLowerCase();
  Serial.println("Serial 1 Input: " + String(rI));
  // ba bb bc br
  // re bl
  if (rI == "ballc" || rI == "bc") {
    Serial1.end();
    if (ROBOT == "red") {
      ball(RED);
    } else if (ROBOT == "blue") {
      ball(BLUE);
    } else {
      Serial.println("Color Error");
    }
    Serial1.begin(ROBORIO_SPEED);
  } else if (rI == "ball" || rI == "ba") {
    matrix.clear();
    ball(WHITE);
  } else if (rI == "ballb" || rI == "bb") {
    matrix.clear();
    ball(BLUE);
  } else if (rI == "ballr" || rI == "br") {
    matrix.clear();
    ball(RED);
  } else if (rI == "red" || rI == "re") {
    ROBOT = "red";
  } else if (rI == "blue" || rI == "bl") {
    ROBOT = "blue";
  } else {
    error("Invalid roboRio input");
  }
}

bool serialInterp () {
  //  if (noSerial) {
  //    Serial.println("Serial is disabled");
  //    return false;
  //  }
  String in;
  in = serialIn();
  in.toUpperCase();
  Serial.println(in);
  if (!(in == "TEST" || in == "TEST\n" || in == "BLING" || in == "BLING\n" || in == "TEAM" || in == "TEAM\n" || in == "OFF" || in == "OFF\n" || in == "ON" || in == "ON\n")) {
    Serial.println("What would you like to do?");
    Serial.println("\ttest");
    Serial.println("\tbling");
    Serial.println("\tteam");
    Serial.println("\toff");
    Serial.println("\ton");
    in = serialIn();
  } else {
    Serial.print("Using original value: ");
    serialBoolOver();
  }
  Serial.println(in);
  in.toUpperCase();
  if (in == "TEST" || in == "TEST\n") {
    if (serialBool("Would you like to enter test mode? ")) {
      testing = !TESTING;
      return true;
    } else {
      return false;
    }
  } else if (in == "BLING" || in == "BLING\n") {
    if (serialBool("Would you like to enable bling? ")) {
      testing = TESTING;
      return true;
    } else {
      return false;
    }
  } else if (in == "TEAM" || in == "TEAM\n") {
    Serial.print("Team Number 1: ");
    int teamA = serialInt();
    Serial.print("Team Number 2: ");
    int teamB = serialInt();
    if (serialBool("Would you like to change teams to " + String(teamA) + " and " + String(teamB) + "? ")) {
      tN[0] = teamA;
      tN[1] = teamB;
      return false;
    } else {
      return false;
    }
  } else if (in == "OFF" || in == "OFF\n") {
    if (serialBool("Would you like to turn off? ")) {
      turnOff = true;
      return true;
    } else {
      return false;
    }
  } else if (in == "ON" || in == "ON\n") {
    if (serialBool("Would you like to turn on? ")) {
      turnOff = false;
      return false;
    } else {
      return false;
    }
  } else {
    Serial.println("invalid");
    return false;
  }
}

bool serialBoolO = false;

bool serialBool (String message) {
  if (serialBoolO) {
    serialBoolO = false;
    return true;
  }
  Serial.print(message);
  String in = serialIn();
  Serial.println(in);
  in.toUpperCase();
  if (in == "Y" || in == "YES" || in == "Y\n" || in == "YES\n") {
    Serial.println("Yes");
    return true;
  } else {
    Serial.println("No");
    return false;
  }
}

void serialBoolOver () {
  serialBoolO = true;
}

String serialIn (int s) {
  if (s == 0) {
    while (Serial.available() < 1) {}
    return Serial.readString();
  } else {
    Serial.println("Serial 1 used");
    while (Serial1.available() < 1) {}
    return Serial1.readStringUntil('\n');
  }
}

int serialInt () {
  while (Serial.available() < 1) {}
  String s =  Serial.readString();
  return s.toInt();
}
