void roboRioSerial() {
  String rI = serialIn(1);
  rI.replace("\n", "");
  //  rI.toUpperCase();
  Serial.println(rI);
  // -----
  String rIC = rI;
  String rIR = rI;
  String rIB = rI;
  String rIA = rI;
  String rB = rI;
  String rR = rI;
  //
  rIC.replace("ballc", "#");
  rIR.replace("ballr", "#");
  rIB.replace("ballb", "#");
  rIA.replace("ball", "#");
  rB.replace("blue", "#");
  rR.replace("red", "#");
  // -----
  if (rIC != rI) {
    if (ROBOT == "red") {
      Serial1.end();
      ball(RED);
      Serial1.begin(ROBORIO_SPEED);
    } else if (ROBOT == "blue") {
      Serial1.end();
      ball(BLUE);
      Serial1.begin(ROBORIO_SPEED);
    } else {
      Serial.println("Color Error");
    }
  } else if (rIR != rI) {
    matrix.clear();
    ball(RED);
  } else if (rIB != rI) {
    matrix.clear();
    ball(BLUE);
  } else if (rIA != rI) {
    matrix.clear();
    ball(WHITE);
  } else if (rR != rI) {
    ROBOT = "red";
  } else if (rB != rI) {
    ROBOT = "blue";
  } else {
    Serial.println("Invalid roboRio input");
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
  if (!(in == "TEST" || in == "TEST\n" || in == "BLING" || in == "BLING\n" || in == "TEAM" || in == "TEAM\n")) {
    Serial.println("What would you like to do?");
    Serial.println("\ttest");
    Serial.println("\tbling");
    Serial.println("\tteam");
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
    int teamA = Serial.parseInt();
    Serial.print("Team Number 2: ");
    int teamB = Serial.parseInt();
    if (serialBool("Would you like to change teams to " + String(teamA) + " and " + String(teamB) + "? ")) {
      tN[0] = teamA;
      tN[1] = teamB;
      return false;
    } else {
      return false;
    }
  }
  else {
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
    return Serial.readStringUntil('\n');
  } else {
    Serial.println("Serial 1 used");
    while (Serial1.available() < 1) {}
    return Serial1.readString();
  }
}
