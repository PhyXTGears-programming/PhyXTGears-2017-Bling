// 255, 255, 150
void runBling (int order[]) {
  int n = ceil(sizeof(blingPrograms) / sizeof(int));
  Serial.println("N: " + String(n));
  Serial.println(sizeof(blingPrograms));
  Serial.println(sizeof(int));
  int co[] = {0, 150, 0};
  int co2[] = {150, 150, 150};
  String me10[3] = {"1720", "PhyXT", "Gears"};
  uint16_t co10[3] = {GREEN, GREEN, GREEN};
  uint16_t c1[] = {matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255), matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255), matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)};
  int loopSize = sizeof(subteams) / sizeof(subteams[0]);
  String tN[] = {"71", "1529", "1720"};
  uint16_t tC[] = {matrix.Color(0, 0, 128), matrix.Color(255, 0, 0), matrix.Color(0, 255, 0)};
  for (int i = 0; i < n; i++) {
    int bCo = random(2);
    Serial.println("Running #" + String(i + 1) + ": " + String(blingPrograms[i]));
    switch (blingPrograms[i]) {
      case 0:
        rDraw(800, matrix.Color(0, 255, 255), 9, 0, true);
        theaterChase(5, 0, matrix.Color(255, 0, 0), true);
        Reset();
        break;
      case 1:
        //        for (int j = 0; j < 9; j++) {
        //          rectangleZoom(0, 0, 40, 16, matrix.Color(0, 25, 112), 9, true);
        //          Reset();
        //        }
        break;
      case 2:
        printText("I'm Spitfire", co, 50, true, true, 1);
        Reset();
        break;
      case 3:
        //        matrix.fillScreen(matrix.Color(255, 255, 150));
        //        updateScreen();
        //        delay(250);
        //        Reset();
        break;
      case 4:
        zigZag(2000, matrix.Color(0, 0, 255), matrix.Color(255, 0, 0), 100, 5);
        Reset();
        break;
      case 5:
        brightOver(255);
        strobePixel(1500, 0, matrix.Color(0, 0, 0), 5, true);
        Reset();
        break;
      case 6:
        brightOver(255);
        strobePixel(1000, 0, matrix.Color(255, 255, 255), 1, false);
        Reset();
        break;
      case 7:
        sinWave(matrix.Color(random(255), random(255), random(255)), 9, 3, float(0.2));
        delay(1000);
        Reset();
        break;
      case 8:
        screenSaver(4500, 8, 6, 7, 50);
        Reset();
        matrix.setFont(&FIRST_FONT);
        printText("First", co2, 21, true, true, 0, 2);
        matrix.setFont(&FONT);
        Reset();
        break;
      case 9:
        spot(7000, 5, 10, true);
        Reset();
        break;
      case 10:
        credits(me10, co10, 3);
        Reset();
        break;
      case 11:
        Serial.println("Loop size: " + String(loopSize));
        credits(subteams, c1, loopSize, 0, 13, true);
        Reset();
      case 12:
        brightOver(BRIGHT - 20);
        audioBar(2500, 5);
        Reset();
        break;
      case 13:
        credits (tN, tC, 2);
        Reset();
        break;
      case 14:
        if (bCo == 0) {
          ball(RED);
        } else {
          ball(BLUE);
        }
        Reset();
        break;
    }
    Serial.print("d");
    Reset();
    Serial.println("one");
    if (Serial.available() > 0) {
      bool a = serialInterp();
      if (a) {
        return;
      }
    }
  }
}
