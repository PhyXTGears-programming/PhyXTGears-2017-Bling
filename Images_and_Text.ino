void printText(String phrase, int color[], int run_time, bool scroll, bool upperCase, int Skip, int pixOffset) {
  int h = matrix.height() - 1;
  h -= pixOffset;
  char p[phrase.length()];
  if (upperCase) {
    phrase.toUpperCase();
  }
  phrase.toCharArray(p, phrase.length());
  clearScreen();
  matrix.setTextColor(matrix.Color(color[0], color[1], color[2]));
  int x;
  if (scroll) {
    x = matrix.width();
    run_time += (phrase.length() * 11) + matrix.width();
  } else {
    x = 0;
  }
  for (int j = 0; j < run_time; j += Skip + 1) {
    clearScreen();
    matrix.setCursor(x, h);
    matrix.print(phrase);
    if ( scroll) {
      x -= Skip + 1;
    }
    delay(0);
    updateScreen();
  }
}

void rectangleZoom(int x, int y, int width, int height, int color, int Delay, bool noFill) {
  int iterations = min(width / 2, height / 2);
  //  int c = 0;
  for (int i = 0; i < iterations; i++) {
    matrix.drawRect(x, y, width, height, color);
    delay(Delay);
    updateScreen();
    if (noFill) {
      matrix.clear();
    }
    x += 1;
    y += 1;
    width -= 2;
    height -= 2;
    //    if (Length < c) {
    //      c += 1;
    //    }
  }
}

/*
  void sinWave (uint16_t color, int Delay, float mult) {
  float w = matrix.width();
  float he = matrix.height();
  float h = he / 2;
  float a = (h - 1) / w;
  float co;
  int c;
  for (int i = 0; i < w; i++) {
    co = i * a;
    c = ceil(h - co);
    double r = sin(i * mult) * double(c);
    Serial.println("X: " + String(i) + " Y: " + String(round(r) + 8) + " C: " + String(c, 9) + " CO: " + String(co));
    matrix.drawPixel((i), (round(r) + 8), color);
    updateScreen();
    delay(Delay);
  }
  delay(Delay * 2);
  }
*/

void spot (unsigned long Stop, int wide, int Delay, bool first) {
  float past = 0.3;
  unsigned long Start = millis();
  Stop += Start;
  //
  uint16_t color = matrix.Color(255, 255, 0);
  // speed vars
  int speedMaxRand = 1501;
  int speedAdd = 350;
  float speedD = 1000.0;
  int speedMinDiff = 600;
  //
  float sp = random(speedMaxRand);
  sp += speedAdd;
  float Speed = sp / speedD;
  Serial.println("Speed: " + String(Speed));
  float loc1 = random(matrix.width() - wide);
  loc1 += wide;
  float a1 = Speed;
  int width = wide;
  //
  float sp2 = random(speedMaxRand);
  if (abs(sp - sp2) < speedMinDiff) {
    while (abs(sp - sp2) < speedMinDiff) {
      Serial.println("Speed reselection");
      sp2 = random(speedMaxRand);
    }
  }
  sp2 += speedAdd;
  float Speed2 = sp2 / speedD;
  Serial.println("Speed: " + String(Speed2));
  float loc2 = random(matrix.width() - wide);
  loc2 += wide;
  float a2 = Speed;
  int width2 = wide;
  //
  int r = 0;
  //
  int rS = 0; // 3      7
  int cS = 0; // 3 even 6
  int tS = 0; // 4 even 7
  int c = 1;
  //
  int cAm = 255;
  int lBi = 255;
  bool Run = true;
  while (Start < Stop) {
    color = matrix.Color(lBi, lBi, 0);
    if (first) {
      int sPosX = (ceil(matrix.width() / 4) * 3) + 1;
      int sPosY = floor(matrix.height() / 2) - 1;
      int tPosX = floor(matrix.width() / 4) - 2;
      int tPosY = floor(matrix.height() / 2) - 0;
      int cPosX = round(matrix.width() / 2) - 0;
      int cPosY = floor(matrix.height() / 2) - 1;
      //
      c++;
      //
      if (rS < 3 && (c % 9) == 0 && cS > 2) {
        rS++;
      }
      if (cS < 3 && (c % 9) == 0 && tS > 3) {
        cS++;
      }
      if (tS < 4 && (c % 9) == 0) {
        tS++;
      }
      //
      if (tS != 0) {
        drawTriangleCenter(tPosX, tPosY, tS, matrix.Color(cAm, 0, 0));
      }
      if (cS != 0) {
        matrix.drawCircle(cPosX, cPosY, cS, matrix.Color(cAm, cAm, cAm));
      }
      if (rS != 0) {
        rectFromCenter(sPosX, sPosY, rS, matrix.Color(0, 0, cAm));
      }
      if ((Stop - Start) < 2500) {
        if ((c % 5) == 0) {
          rS++;
          cS++;
          tS++;
        }
        cAm -= 10;
        if (cAm <= 0) {
          first = false;
        }
      }
    }
    if (Run) {
      matrix.fillTriangle(5, (matrix.height() - 1), (round(loc1) - width), 0, round(loc1), 0, color);
      matrix.fillTriangle((matrix.width() - 6), (matrix.height() - 1), (round(loc2) - width), 0, round(loc2), 0, color);
      updateScreen();
    }
    matrix.clear();
    //
    loc1 += a1;
    //    Serial.print("1: ");
    //    Serial.println(loc1);
    if (loc1 > (matrix.width() * (past + 1))) {
      loc1 -= 2;
      a1 = Speed;
      a1 = a1 * -1;
    }
    if ((loc1 - width) < ((past * 40.0) * -1)) {
      loc1 += 2;
      a1 = Speed;
    }
    if (loc1 > 20) {
      width = wide + 1;
    }
    if (loc1 > 40) {
      width = wide + 2;
    }
    if (loc1 > 40) {
      width = wide + 1;
    }
    if (loc1 > 20) {
      width = wide;
    }
    //
    loc2 += a2;
    //    Serial.println(loc2);
    if (loc2 > (matrix.width() * (past + 1))) {
      loc2 -= 2;
      a2 = Speed2;
      a2 = a2 * -1;
    }
    if ((loc2 - width2) < ((past * 40.0) * -1)) {
      loc2 += 2;
      a2 = Speed2;
    }
    if (loc2 > 20) {
      width2 = wide + 1;
    }
    if (loc2 > 40) {
      width2 = wide + 2;
    }
    if (loc2 > 40) {
      width2 = wide + 1;
    }
    if (loc2 > 20) {
      width2 = wide;
    }
    //
    if ((Stop - Start) < 1000) {
      if (lBi <= 15) {
        Run = false;
      }
      lBi -= 13;
    }
    //
    delay(Delay);
    Start = millis();
  }
}

void rectFromCenter (int centerX, int centerY, int radius, uint16_t color) {
  int a = radius * 2;
  a++;
  matrix.drawRect((centerX - radius), (centerY - radius), a, a, color);
  //  Serial.println("X: " + String(centerX) + " Y: " + String(centerY) + " R: " + String(radius));
}

float getSpeedVal (float s, float mi, float ma) { // mi = 0.5;   ma = 2;      mi = 0.3;   ma = 3;
  // half of values <1 other half >1
  // put 1 in with <1
  int miI = round(mi * 100.0);    // 50       30
  int maI = round(ma * 100.0);    // 200      300
  float s1 = random(maI - miI);   // 0-150    0-270
  if (s <= miI) {
    s += 50;                      // 50-100   30-80
  } else if (s > miI) {
    s *= 2;
  }
}

void sinWave (uint16_t color, int Delay, int n, float mult) {
  float w = matrix.width() * n;
  float he = matrix.height();
  float h = he / 2;
  float a = (h - 1) / w;
  float co;
  int c;
  for (int i = 0; i < w; i++) {
    co = i * a;
    c = ceil(h - co);
    double r = sin(i * mult) * double(c);
    //    Serial.println("X: " + String(i) + " Y: " + String(round(r) + 8) + " C: " + String(c, 9) + " CO: " + String(co));
    matrix.drawPixel(floor(i / n), (round(r) + 8), color);
    updateScreen();
    delay(Delay);
  }
  delay(Delay * 2);
  int bri = BRIGHT;
  for (int i = 0; i < 15; i++) {
    if (bri > ceil(BRIGHT / 15.0)) {
      bri -= ceil(BRIGHT / 15.0);
    } else {
      bri = 0;
    }
    brightOver(bri);
    updateScreen();
    delay(Delay);
  }
  Reset();
}

const double piOver = 3.14159265358979323846264338327950 / 180;

void sinWaveM (uint16_t color, int Delay, unsigned long Stop, float n, float s) {
  unsigned long Start = millis();
  Stop += Start;
  int w = round(matrix.width() * n);
  bool ad = false;
  int he = floor(matrix.height() / 2.0);
  float c = he;
  while (Start < Stop) {
    for (int i = 0; i < w; i++) {
      float Sin = sin((i * piOver));
      float si = Sin * c;
      Serial.println("X: " + String(round(i / n)) + ", Y: " + String(round(si) + 8) + ", I: " + String(i) + ", Sin: " + String(Sin, 3) + ", Si: " + String((si + 8.0), 3));
      matrix.drawPixel(round(i / n), round(si) + 8, color);
    }
    if (ad) {
      c += s;
    } else {
      c -= s;
    }
    if (c > he) {
      c = 8 - c;
      ad = false;
    }
    if (c < 0) {
      c = 0 - c;
      ad = true;
    }
    matrix.show();
    matrix.clear();
//    delay(Delay);
  }
  Start = millis();
}
