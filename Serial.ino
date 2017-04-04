void roboRioSerial() {
  String rI = serialIn(1);
  //  rI.toUpperCase();
  Serial.println(rI);
  if (rI == "ball") {
    matrix.clear();
    ball(WHITE);
  } else if (rI == "ballb") {
    matrix.clear();
    ball(BLUE);
  } else if (rI == "ballr") {
    matrix.clear();
    ball(RED);
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
  while (Serial.available() > 0) {
    in = Serial.readString();
  }
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

bool serialBool (String message) {
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

String serialIn (int s) {
  if (s == 0) {
    while (Serial.available() < 1) {}
    return Serial.readString();
  } else {
    Serial.println("Serial 1 used");
    while (Serial1.available() < 1) {}
    return Serial1.readString();
  }
}
