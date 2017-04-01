const int randThreshold = 50;

void audioBar (unsigned int Stop, int width) {
  unsigned int Start = millis();
  Stop += Start;
  if (matrix.width() % width != 0) {
    Serial.println("Audio Bar: Width not evenly divisible by " + String(matrix.width()));
    return;
  }
  int m = matrix.height();
  int n = matrix.width() / width;
  Serial.println("Audio Bar: " + String(n) + " bars with a width of " + String(width));
  int vals[n][2];
  uint16_t barCols[n];
  for (int i = 0; i < n; i++) {
    vals[i][0] = random(m);
    vals[i][1] = random(2);
    barCols[i] = randColBr();
  }
  while (Start < Stop) {
    int ind = 0;
    for (int i = 0; i < 40; i += width) {
      matrix.fillRect(i, (matrix.height() - vals[ind][0]), width, vals[ind][0], barCols[ind]);
      ind++;
    }
    for (int i = 0; i < n; i++) {
      int mB = moveBar(vals[i][1]);
      vals[i][1] = mB;
      if (mB == 0) {
        vals[i][0] -= 1;
        if (vals[i][0] < 0) {
          vals[i][0] = 1;
          vals[i][1] = 1;
        }
      } else if (mB == 1) {
        vals[i][0] += 1;
        if (vals[i][0] > matrix.height()) {
          vals[i][0] = matrix.height() - 1;
          vals[i][1] = 0;
        }
      } else {
        Serial.println("Audio Bar Error");
        return;
      }
    }
//    Serial.println("H: " + String(vals[0][0]));
//    Serial.println("D: " + String(vals[0][1]));

    updateScreen();
    delay(5);
    matrix.clear();
    Start = millis();
  }
}

int moveBar (int d) {
  int r = random(3);
  if (r < 2) {
    return d;
  } else {
    return (d + 1) % 2;
  }
}
