void strobePixel(unsigned long Stop, int Delay, int color, int num, bool Rand) {
  unsigned long Start = millis();
  Stop += Start;
  while (Start < Stop) {
    for (int i = 0; i < num; i++) {
      Start = millis();
      //    int a[] = {};
      if (Rand) {
        color = matrix.Color(random(256), random(256), random(256));
      }
      matrix.drawPixel(random(matrix.width()), random(matrix.height()), color);
    }
    updateScreen();
    clearScreen();
    Start = millis();
    delay(Delay);
    Start = millis();
  }
}

void theaterChase(int Skips, int Delay, int color, bool bow) {
  for (int i = 0; i < matrix.height(); i += 2) {
    int Sum = 0;
    for (int j = 0; j < matrix.width(); j += Skips) {
      if (bow) {
        color = Wheel( ((i * matrix.width()) + j) % 255);
      }
      Sum += Skips;
      matrix.drawPixel(j, i, color);
      delay(Delay);
      updateScreen();
      matrix.drawLine(0, i, Sum, i, matrix.Color(0, 0, 0));
    }
    Sum =  0;
    for (int j = matrix.width(); j > 0; j -= Skips) {
      if (bow) {
        color = Wheel( (i * matrix.width()) + matrix.width() +  (Skips * -1) % 255);
      }
      Sum += Skips;
      matrix.drawPixel(j, i + 1, color);
      delay(Delay);
      updateScreen();
      matrix.drawLine(matrix.width(), i + 1, matrix.width() - Sum, i + 1, matrix.Color(0, 0, 0));
    }
  }
  delay(Delay);
  updateScreen();
}

void zigZag(unsigned long Stop, uint16_t color, uint16_t color2, int d, int gap) {
  unsigned long Start = millis();
  Stop += millis();
  //  while (Start < Stop){
  //    for(int i = 0; i < matrix.height(); i++){
  //      for(int j = 0; j < matrix.width(); j++){
  //        for
  //      }
  //    }
  //  }
  int x = 0;
  while (Start < Stop) {
    for (int i = 0; i < matrix.height(); i += 2) {
      for (int j = (0 + x); j < matrix.width(); j += (gap + 1)) {
        matrix.drawPixel(j, i, color);
      }
    }
    for (int i = 1; i < matrix.height(); i += 2) {
      for (int j = (matrix.width() - (x + 1)); j > 0; j -= (gap + 1)) {
        matrix.drawPixel(j, i, color2);
      }
    }
    updateScreen();
    matrix.clear();
    x++;
    if (x > gap) {
      x = 0;
    }
    delay(d);
    Start = millis();
  }

}

void rDraw(unsigned long Stop, uint16_t color, int n, int Delay, bool Random) {
  unsigned long Start; //Guarantees at least 1 iteration.
  int i = 0;
  Stop += millis();
  while (Start < Stop) {
    if (Random) {
      color = matrix.Color(random(250), random(220), random(170));
    }
    matrix.drawPixel(random(0, matrix.width() + 1), random(0, matrix.height() + 1), color);
    if (i % n == 0 && i != 0) {
      updateScreen();
      delay(Delay);
    }
    Start = millis();
    i++;
  }
}

void fill (int per) {
  for (int x = 0; x < matrix.width(); x++) {
    for (int y = 0; y < matrix.height(); y++) {
      int r = random(99);
      if (r >= (100 - per)) {
        matrix.drawPixel(x, y, matrix.Color(random(256), random(256), random(256)));
      }
    }
  }
  updateScreen();
}
