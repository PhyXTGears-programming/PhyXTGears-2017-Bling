void loadBitmap () {
  Serial.println("Start loading bitmap...");
  unsigned long s = micros();
  unsigned long l = EEPROM.read(0);
  unsigned long w = EEPROM.read(1);
  unsigned long n = l * w * 3;
  Serial.println(n);
  for (unsigned long i = 0; i < n; i++) {
    firstLogo[i] = EEPROM.read(i + 2);;
    //    Serial.println(i);
  }
  Serial.println("loaded a " + String(l) + "x" + String(w) + " array (" + String(l * w) + " pixels) in " + String(float(micros() - s) / 1000, 3) + " milliseconds");
}

void printBitmap(unsigned char b[]) {
  Serial.println("Start printing bitmap...");
  unsigned long s = micros();
  unsigned long l = EEPROM.read(0);
  unsigned long w = EEPROM.read(1);
  unsigned long n = l * w * 3;
  unsigned long pos;
  Serial.println(n);
  for (unsigned long i = 0; i < l; i++) {
    for (unsigned long j = 0; j < w; j++) {
      matrix.drawPixel(j, i, matrix.Color(b[pos + 1], b[pos + 1], b[pos + 0]));
      //      Serial.println("x: " + String(j) + ", y: " + String(i) + ", pos: " + String(pos));
      pos += 3;
    }
  }
  unsigned long d = micros();
  matrix.show();
  unsigned long c = micros();
  Serial.print("printed a " + String(l) + "x" + String(w) + " array (" + String(l * w) + " pixels) in " + String(float(c - s) / 1000, 3) + " milliseconds.");
  Serial.println(" Show took " + String(float(c - d) / 1000, 3) + " milliseconds");
}
