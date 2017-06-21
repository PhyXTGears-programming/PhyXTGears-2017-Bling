/*
  void Loop(){
  matrix.setBrightness(50);
  getPos();
  Time = millis();
  if (Time >= lastTime + ballSpeed) {
    lastTime += ballSpeed;
    go = true;
  }
  else {
    go = false;
  }
  if (ballX > matrix.width() - 2) {
    ballDirectionX = -1;
  }
  if (ballY > matrix.height() - 2) {
    ballDirectionY = -1;
  }
  if (ballY < 1) {
    ballDirectionY = 1;
  }
  if (ballX < 1 && ballX > -1 && go == true) {
    if (paddleY <= ballY && paddleY >=  ballY - paddleSize) {
      ballDirectionX = 1;
      Score++;
      Serial.print("Scores: " + String(Score));
    }
    else {
      Score = 0;
      gameOver = true;
      Serial.print("\n\tGAME OVER");

      Serial.print("\tYou ended with a score of " + String(Score) + ".");
      ballX = matrix.width() / 2;
      ballY = matrix.height() / 2;
    }
  }
  if (go == true) {
    ballX += ballDirectionX;
    ballY += ballDirectionY;
  }
  }
  void getPos() {
  float sensorValue = analogRead(sensorPin) / 24;
  if (sensorValue >= 15 - paddleSize) {
    paddleY = 15 - paddleSize;
  }
  else if (sensorValue <= 0) {
    paddleY = 0;
  }
  else {
    paddleY = sensorValue;
  }
  }

  void loop() {
  matrix.fillScreen(matrix.Color(0, 0, 0));
  matrix.drawPixel(ballX, ballY, matrix.Color(0, 255, 0));
  matrix.drawLine(paddleX, paddleY, paddleX, paddleY + paddleSize, matrix.Color(255, 255, 255));
  if (gameOver == true) {
    int a = 0;
    matrix.setCursor(0, 0);
    matrix.print("GAME OVER");
  }
  updateScreen(); //UPDATESCREEN
  }
*/

int getPos(int pos, int dir, int Size) {
  if (pos >= Size - 1 && dir != -1) {
    dir = -1;
  }
  else if (pos <= 0 && dir != 1) {
    dir = 1;
  }
  //  Serial.println("Dir: " + String(dir));
  return dir;
}

int getRandom() {
  int a = random(2);
  if (a == 0) {
    a = -1;
  }
  return a;
}

void screenSaver(unsigned long Stop, int tSize, int cSize, int sSize, int Speed) {
  float sPosX = (ceil(matrix.width() / 4) * 3) - 2;
  float sPosY = floor(matrix.height() / 2) - 4;
  int sDirX = getRandom();
  int sDirY = getRandom();
  float tPosX = floor(matrix.width() / 4) - 3;
  float tPosY = floor(matrix.height() / 2) - 0;
  int tDirX = getRandom();
  int tDirY = getRandom();
  float cPosX = round(matrix.width() / 2) - 1;
  float cPosY = floor(matrix.height() / 2) - 1;
  int cDirX = getRandom();
  int cDirY = getRandom();
  unsigned long Start = millis(); //used for how run time of program
  unsigned long Keep = millis(); //used for physics
  unsigned long Stay = 0; //used for physics
  Stop += millis();
  matrix.drawCircle(cPosX, cPosY, ceil(cSize / 2), matrix.Color(255, 255, 255));
  matrix.drawRect(sPosX, sPosY, sSize, sSize, matrix.Color(0, 0, 255));
  drawTriangleCenter(tPosX, tPosY, tSize / 2, matrix.Color(255, 0, 0));
  updateScreen();
  delay(500);
  float speeds[3] = {0, 0, 0}; // C, S, T
  for (int i = 0; i < 3; i++) {
    float s = random(76);
    if (s <= 50) {
      s += 50;
    } else if (s > 50) {
      s *= 2;
    }
    s += 30;
    s = s / 100.0;
    speeds[i] = s;
    Serial.print("Speed " + String(i) + ": ");
    Serial.println(speeds[i]);
  }
  while (Start < Stop) {
    Keep = millis();
    Stay = 0;
    cDirX = getPos(cPosX, cDirX, matrix.width());
    cDirY = getPos(cPosY, cDirY, matrix.height());
    sDirX = getPos(sPosX, sDirX, matrix.width());
    sDirY = getPos(sPosY, sDirY, matrix.height());
    tDirX = getPos(tPosX, tDirX, matrix.width());
    tDirY = getPos(tPosY, tDirY, matrix.height());
    cPosX += cDirX * speeds[0];
    cPosY += cDirY * speeds[0];
    sPosX += sDirX * speeds[1];
    sPosY += sDirY * speeds[1];
    tPosX += tDirX * speeds[2];
    tPosY += tDirY * speeds[2];
    //    Serial.println(sPosX);
    //    Serial.println(sPosY);
    clearScreen();
    matrix.drawCircle(round(cPosX), round(cPosY), ceil(cSize / 2), matrix.Color(255, 255, 255));
    matrix.drawRect(round(sPosX), round(sPosY), sSize, sSize, matrix.Color(0, 0, 255));
    //matrix.drawTriangle(tPosX, tPosY,  tPosX, tPosY + tSize, tPosX + tSize, tPosY, matrix.Color(255, 0, 0));
    drawTriangleCenter(round(tPosX), round(tPosY), tSize / 2, matrix.Color(255, 0, 0));
    updateScreen();
    delay(Speed);
    Start = millis();
  }
}

void drawTriangleCenter (int centerX, int centerY, int radius, uint16_t color) {
  double sqT = sqrt(3) * double(double(1) / double(3));
  double yL = double(centerY) + (0.5 * radius);
  double side = radius / (2 * sqT);
  int s = ceil(side);
  matrix.drawTriangle((centerX - s), yL, centerX, (centerY - radius), (centerX + s), yL, color);
}
