void printText (String phrase, int color[], int run_time, bool scroll, bool upperCase, int Skip, int pixOffset) {
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

void rectangleZoom (int x, int y, int width, int height, int color, int Delay, bool noFill) {
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

void creditsPrint (String message, uint16_t color, int Delay, bool twoText, String message2, uint16_t color2, bool threeText, String message3, uint16_t color3, bool allCaps, int endDelay) {
  matrix.setFont();
  if (allCaps) {
    message.toUpperCase();
    message2.toUpperCase();
    message3.toUpperCase();
  }
  int h = matrix.height();
  for (int i = 0; i >= -8; i--) {
    if (twoText) {
      matrix.setTextColor(color2);
      matrix.setCursor(0, i + 8);
      matrix.print(message2);
    }
    if (threeText) {
      matrix.setTextColor(color3);
      matrix.setCursor(0, i + 16);
      matrix.print(message3);
    }
    matrix.setTextColor(color);
    matrix.setCursor(0, i);
    matrix.print(message);
    updateScreen();
    matrix.clear();
    delay(Delay);
  }
  delay(Delay);
  delay(endDelay);
}


void credits (String messages[], uint16_t colors[], int Delay) {
  float Size = sizeof(messages);
  float SizeString = sizeof(String);
  Serial.println(Size);
  Serial.println(SizeString);
  int L = Size / SizeString;
  Serial.println(L);
  creditsPrint ("", matrix.Color(0, 0, 0), 500, true, "", matrix.Color(0, 0, 0), true, messages[0], colors[0]);
  delay(Delay);
  Serial.println("A");
  creditsPrint ("", matrix.Color(0, 0, 0), 500, true, messages[0], colors[0], true, messages[1], colors[1]);
  delay(Delay);
  //
  Serial.println("POINT");
  //
  creditsPrint ("", matrix.Color(0, 0, 0), 500, true, "", matrix.Color(0, 0, 0), true, messages[0], colors[0]);
  delay(Delay);
  Serial.println("B");
  creditsPrint (messages[L - 2], colors[L - 2], 500, true, messages[L - 1], colors[L - 1], true, "", matrix.Color(0, 0, 0));
  delay(Delay);
}

