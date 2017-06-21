void gear (int x, int y, uint16_t color) {
  matrix.fillCircle(x, y, 9, color);
  // ---
  gear_UL(x, y, color); // Upper Left
  gear_UR(x, y, color); // Upper Right
  gear_LL(x, y, color); // Lower Left
  gear_LR(x, y, color); // Lower Right
  gear_LC(x, y, color); // Lower Center
  // ---
  matrix.drawPixel(x, y, BLUE); // Center
  updateScreen(); // UPDATESCREEN
}

void gear_UL (int x, int y, uint16_t color) {
  matrix.drawPixel(x - 1, y - 2, BLUE); // center
  matrix.drawPixel(x - 7, y - 4, BLUE); // lower left
  matrix.drawPixel(x - 1, y - 9, BLUE); // upper
  matrix.fillTriangle(x - 1, y - 2, x - 7, y - 4, x - 1, y - 10, BLUE);
}

void gear_UR (int x, int y, uint16_t color) {
  matrix.drawPixel(x + 1, y - 2, BLUE); // center
  matrix.drawPixel(x + 7, y - 4, BLUE); // lower right
}

void gear_LL (int x, int y, uint16_t color) {
  matrix.drawPixel(x - 2, y, BLUE); // center
  matrix.drawPixel(x - 6, y + 5, BLUE); // lower
  matrix.drawPixel(x - 8, y - 2, BLUE); // upper
}

void gear_LR (int x, int y, uint16_t color) {
  matrix.drawPixel(x + 2, y, BLUE); // center
  matrix.drawPixel(x + 6, y + 5, BLUE); // lower
  matrix.drawPixel(x + 8, y - 2, BLUE); // upper
}

void gear_LC (int x, int y, uint16_t color) {
  matrix.drawPixel(x, y + 2, BLUE); // center
  matrix.drawPixel(x - 4, y + 7, BLUE); // left
  matrix.drawPixel(x + 4, y + 7, BLUE); // right
}
