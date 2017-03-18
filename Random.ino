void randSeed () {
  int an1 = analogRead(A1);
  if (an1 == 0) {
    an1 = analogRead(A11);
    if (an1 == 0) {
      an1 = analogRead(A1);
      if (an1 == 0) {
        an1 = 1;
      }
    }
  }
  int an2 = analogRead(A2);
  if (an2 == 0) {
    an2 = analogRead(A12);
    if (an2 == 0) {
      an2 = analogRead(A15);
      if (an2 == 0) {
        an2 = 1;
      }
    }
  }
  int an3 = analogRead(A3);
  if (an3 == 0) {
    an3 = analogRead(A13);
    if (an3 == 0) {
      an3 = analogRead(A15);
      if (an3 == 0) {
        an3 = 1;
      }
    }
  }
  int an4 = analogRead(A4);
  if (an4 == 0) {
    an4 = analogRead(A14);
    if (an4 == 0) {
      an4 = analogRead(A15);
      if (an4 == 0) {
        an4 = 1;
      }
    }
  }
  double randSeedVal = an1 * an2 * an3;
  while (randSeedVal > 3097152) {
    randSeedVal = randSeedVal / 2097651;
  }
  an4 = an4 / 2;
  randSeedVal = randSeedVal * an4;
  Serial.print("Seed: ");
  randomSeed(randSeedVal);
  Serial.println(randSeedVal);
}
