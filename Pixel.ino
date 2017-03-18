void pixelAlert () {
  Serial.println("...");
  while (digitalRead(gearSensePin) == LOW) {
    Serial.print("o");
    printToString(gearString, 0, 255, 0);
    Serial.println("n");
    delay(100);
    printToString(gearString, 0, 0, 0);
    delay(100);
    Serial.println("1");
  }
  Serial.println("off");
}

void printToString (Adafruit_NeoPixel p, int r, int g, int b) {
  int n = gearStringNum;
  for (int i = 0; i < n; i++) {
    //    if (i % 7 != 0) {
    gearString.setPixelColor(i, r, g, b);
    Serial.println(i);
    //    }
  }
  gearString.show();
}
