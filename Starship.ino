//void writeTextFile (string File, string dataWrite, bool append = false) {
//  std::ofstream myfile;
//  if (append) {
//    myfile.open(File, std::fstream::out | std::fstream::app);
//  } else {
//    myfile.open(File, std::fstream::out);
//  }
//  myfile << dataWrite;
//  myfile.close();
//}

void explodingCircle (int x, int y, int radius, uint16_t color, bool fill) {
  matrix.drawCircle(x, y, radius, color);
  if (fill){
    matrix.fillCircle(x, y, radius, color);
  }
  updateScreen();
  delay(200);
  for(int i = 0; i < radius * 2; i++){
    matrix.clear();
    for(int j = 0; j < radius * 1.5; j++){
      //KEEP THIS: matrix.drawPixel(random(x - r + i, x + r + 2 + i), random(y - r + i, y + r + 2 + i), color);
      matrix.drawPixel(random(x + radius + i - 4, x + radius + i), random(y + radius + i - 4, y + radius + i))
      matrix.drawPixel(random(x + radius + i - 4, x + radius + i), random(y - radius - i - 4, y - radius - i))
      matrix.drawPixel(random(x - radius + 4, x - radius - i), random(y + radius + i - 4, y + radius + i))
      matrix.drawPixel(random(x - radius - i), random(x - radius - i))
    }
    updateScreen();
    delay(100);
  }
}

void drawShipTL (int x, int y, float s, uint16_t color) {
  // Left side
  matrix.drawLine(x, y, round(x + s), y, color);
    // long
  matrix.drawLine(x, y, x, round(y + (4 * s)), color);
  matrix.drawLine(x, round(y + (4 * s)), round(x + s), round(y + (4 * s)), color);

  // Middle
  int rX = x + (9 * s);
  int rY = round(y + round((4 * s) / 2.0));
//  int mY = round(y / 2.0);
  matrix.drawLine(x, rY, rX, rY, color);
  matrix.fillCircle((round((rX - x) / 2.0) + x), rY, (s * 2), color);

  // Right side
    // long
  matrix.drawLine(rX, y, rX, round(y + (4 * s)), color);
  matrix.drawLine(rX, y, rX - s, y, color);
  matrix.drawLine(rX, round(y + (4 * s)), rX - s, round(y + (4 * s)), color);

  updateScreen();
}

void drawShip (int x, int y, float s, uint16_t color) {
  int X = x;
  int Y = y;
  X -= round(4.5 * s);
  Y -= round((round(y + (4 * s)) - y) / 2.0);
  drawShipTL (X, Y, s, color);
}

