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
