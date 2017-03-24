uint16_t randCol () {
  return matrix.Color(random(randThreshold, 256), random(randThreshold, 256), random(randThreshold, 256));
}

uint16_t randColBr() {
  int c[3];
  int nZ = 0;
  bool go = true;
  while (go) {
    for (int i = 0; i < 3; i++) {
      int v = random(2);
      if (v == 0) {
        c[i] = 0;
        nZ++;
      } else {
        c[i] = 255;
      }
    }
    if (nZ > 2) {
      nZ = 0;
    } else {
      go = false;
    }
  }
  return matrix.Color(c[0], c[1], c[2]);
}

