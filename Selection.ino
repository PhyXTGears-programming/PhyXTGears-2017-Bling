String output;

void blingSelect () {
  Serial.println("Start bling selection...");
  unsigned long s = micros();
  int n = -10;
  bool ru = true;
  int tr = 1;
  while (ru) {
    Serial.print("Attempt " + String(tr) + ":");
    n = selectRandArray();
    if (n > -3) {
      ru = false;
      Serial.println(" success!");
    } else {
      Serial.println(" fail");
    }
    tr++;
  }
  Serial.println(output);
  Serial.println("selected random array containing " + String(n) + " programs in " + String(float(micros() - s) / 1000, 3) + " milliseconds\n");
}

int selectRandArray () {
  output = "";
  for (int i = 0; i < PROGS; i++) {
    progRuns[i] = 0;
  }
  int f = 0;
  if (oneOfEach) {
    int ti = 0;
    for (int j = 0; j < PROGS; j++) {
      ti += progLimit[j];
    }
    for (int i = 0; i < ti; i += 0) {
      int val = random(PROGS);
      bool limitR = (progRuns[val] >= progLimit[val]);
      bool lastSame = (blingPrograms[i - 1] == val);
      bool both = limitR || lastSame;
      both = !both;
      if (i == 0) {
        both = true;
      }
      //      Serial.println("\n" + String(limitR) + "\n" + String(lastSame) + "\n" + String(both));
      if (both) {
        progRuns[val] = progRuns[val] + 1;
        blingPrograms[i] = val;
        i++;
        f = 0;
        output += (String(i) + ": " + String(val));
        output += "\n";
      } else {
        f++;
      }
      if (f > 9) {
        return -9;
      }
    }
    for (int k = 0; k < PROGS; k++) {
      output += ("L: " + String(progLimit[k]) + " R: " + String(progRuns[k]));
      output += "\n";
    }
    return ti;
  } else {
    return -1;
  }
}
