void explodingCircle (int x, int y, int r, uint16_t color) {
<<<<<<< HEAD
  //  matrix.fillCircle(x, y, r);
}

void drawShip (int x, int y, float s, uint16_t color) {
  // Left side
  matrix.drawLine(x, y, round(x + s), y, color);
  matrix.drawLine(x, y, x, round(y + (4 * s)), color);
  matrix.drawLine(x, round(y + (4 * s)), round(x + s), round(y + (4 * s)), color);

  // Middle
  int rX = x + (10 * s);
  int rY = round((y + (4 * s)) / 2.0);
  matrix.drawLine(x, round((y + (4 * s)) / 2.0), rX, rY, color);
//  matrix.fillCircle();

  updateScreen();
=======
  matrix.fillCircle(x, y, r);
}

void drawShip (int x, int y, float s) {
  matrix.drawLine();
>>>>>>> master
}

