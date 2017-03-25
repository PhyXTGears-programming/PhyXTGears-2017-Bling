#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <EEPROM.h>

#define MATRIX              6
#define pixyRingPin         8
#define gearStringPin       7

#define potentiometerPIN    A0
#define gearSensePin        41 // =========

#define pixyRingNum         00
#define gearStringNum       16

#define WIDTH               40  // each
#define HEIGHT              8   // each
#define NUMBER              2   // number high

#define PROGS               13  // programs that exist
#define ToRUN               11   // # to run (if oneOfEach is false) (if true, must equal number of progams being run)
const bool oneOfEach =      true;

#define OVER                true
#define BRIGHT              55

#define FONT                FreeSerif12pt7b
#define FIRST_FONT          FreeSansBoldOblique9pt7b

#define RED                 matrix.Color(255, 0, 0)
#define GREEN               matrix.Color(0, 255, 0)
#define BLUE                matrix.Color(0, 0, 255)
#define YELLOW              matrix.Color(255, 255, 0)
#define AQUA                matrix.Color(0, 255, 255)
#define VIOLET              matrix.Color(255, 0, 255)
#define WHITE               matrix.Color(255, 255, 255)
#define BLACK               matrix.Color(0, 0, 0)

//#define VERTICAL_FONT

//Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, 1, NUMBER, MATRIX, NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_COLUMNS + NEO_TILE_ZIGZAG + NEO_MATRIX_COLUMNS + NEO_MATRIX_TOP + NEO_MATRIX_BOTTOM + NEO_MATRIX_ZIGZAG  + NEO_GRB + NEO_KHZ800);
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, 1, NUMBER, MATRIX, NEO_TILE_BOTTOM + NEO_TILE_RIGHT + NEO_TILE_COLUMNS + NEO_TILE_ZIGZAG + NEO_MATRIX_COLUMNS + NEO_MATRIX_TOP + NEO_MATRIX_BOTTOM + NEO_MATRIX_ZIGZAG  + NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixyRing   = Adafruit_NeoPixel(pixyRingNum, pixyRingPin,   NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel gearString = Adafruit_NeoPixel(gearStringNum, gearStringPin, NEO_GRB + NEO_KHZ800);

int ledNumber;

const String subteams[23] = {"Shout-", " out", "to our", "sub-", " teams", "Media", "Chair-", " mans", "CAD", "Anim-", " ation",
                             "Wood-", " work-", "  ing", "Fund-", " rais-", "  ing", "Out-", " reach", "Scout-", " ing", "Spirit"
                            };

/*
   sound bars
   reversing sine wave / moving sine wave
   fire
*/

// bitmaps

unsigned char firstLogo[40 * 16 * 3];
int firstLogoL;
int firstLogoW;

// ---Selection---
// 0 and 2
/*
  0: Dots
  1: Rectangle zoom (disabled)
  2: name
  3: fill for 0.25 sec (disabled)
  4 : zig - zag
  5 : strobe multi
  6 : strobe white
  7 : sine
  8 : Logo (screensaver)
  9 : Spotlight
  10: 1720
  11: Honors
  12: Thank you 447 for lunch
*/

//                          // one of each true (false)
//                      0  1  2  3  4  5  6  7  8  9 10 11 12
int progLimit[PROGS] = {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};  // Limit for each program (or ratio)
int progRuns[PROGS];        // Number of times each has been selected (nothing)
int blingPrograms[ToRUN];   // order

// ----

bool progBright = false;
int bright;

// ----

// ==============================================

void zigZag(unsigned long Stop, uint16_t color = matrix.Color(255, 255, 255), uint16_t color2 = matrix.Color(255, 255, 255), int d = 100, int gap = 1);
void printText(String phrase, int color[], int run_time = 0, bool scroll = true, bool upperCase = true, int Skip = 0, int pixOffset = 0); //run_time should be set to at least 100 if your font is at 12pt
void printBitMap(int b[], unsigned long Stop, bool scroll = false); //Prints from bitmap, "int b[]".
void rectangleZoom(int x, int y, int width, int height, int color, int Delay = 99, bool noFill = false); //Creates rectangles inside rectangle one by one.
void rainbow(); //Fills matrix with colors then cycles through color wheel. The rough time that this takes to execute is: 4 Seconds.
void strobePixel(unsigned long Time, int Delay, int color, int num, bool Rand); //Strobes random pixel on screen then clears screen and strobes another one.
void theaterChase(int Skips = 1, int Delay = 0, int color = matrix.Color(255, 255, 255), bool bow = false); //Goes through all pixels in matrix clearing screen every time a new pixel is shown.
void rDraw(unsigned long Stop, uint16_t color, int n = 3, int Delay = 10, bool Random = false); //Draws random pixels onto screen does NOT clear every time new pixel is shwon.
void theaterChaseRainbow(int Skips, int Delay = 10); //Does same thing as theater chase only this time it changes color from color wheel. The rough time that this takes to execute is: 3 Seconds.
void brightnessControl(); //Gets value from sensor then divides value by 8.6 sets brightness to that value.
void drawShape(int shape, int values[], int color[]); //Rectangle: 0, Circle: 1, Triangle: 2, Line: 3, Pixels: 4, RoundRectangle: 5.
void generateRGB(); //Randomizes values inside randomRGB.
void sinWave (uint16_t color, int Delay, int n = 1, float mult = float(10));
void screenSaver(unsigned long Stop, int tSize, int cSize, int sSize, int Speed = 35);
void creditsPrint(String message, uint16_t color, int Delay, bool twoText = false, String message2 = "", uint16_t color2 = matrix.Color(255, 255, 255), bool threeText = false, String message3 = "", uint16_t color3 = matrix.Color(255, 255, 255), bool allCaps = true, int endDelay = 0);
void credits (String Messages[], uint16_t colors[], int LoopSize, int Delay = 0, int scrollDelay = 25, bool randColor = false);

// ==============================================

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);
  Serial.println('\n');
  ledNumber = WIDTH * HEIGHT * NUMBER;
  setupPins();
  //  loadBitmap();
  matrix.begin();
  matrix.show();
  gearString.begin();
  gearString.show();
  matrix.setTextWrap(false); //Does weird things if you don't include this.
  matrix.setTextColor(matrix.Color(255, 0, 0));
  matrix.setFont(&FONT);
  matrix.setBrightness(100);
  Serial.println("Microseconds: " + String(micros()));
  brightnessControl();
  randSeed();
  blingSelect();

  //  printBitmap(firstLogo);
}

void loop() {
  // put your main code here, to run repeatedly:
  //    int co[] = {0, 0, 255};
  //    printText("hi", co, 10, false);
  //    theaterChase(3, 0, matrix.Color(0, 255, 0), true);
  //  strobePixel(1000, 0, matrix.Color(255, 255, 255));
  //  rectangleZoom(0,0,32,16, matrix.Color(255, 0, 0), 0);
  //  matrix.fillScreen(matrix.Color(200, 200, 200));
  //  matrix.show();
  //  matrix.clear();
  //  matrix.show();
  //  rDraw(800, matrix.Color(0, 255, 255), 9, 0, true);
  //  matrix.clear();
  //  updateScreen();
  //  delay(300);

  //  if (digitalRead(gearSensePin) == LOW) {
  //    Serial.println("on***");
  //    pixelAlert();
  //    Serial.println("off***");
  //  }
  //  delay(99);
  //  printToString(gearString, 200, 0, 200);
  //  zigZag(5000, matrix.Color(255, 0, 0));


  //  runBling(blingPrograms);
  //  Reset();
  //  blingSelect();  delay(100);
  //  drawTriangleCenter(matrix.width() / 4, matrix.height() / 2, 3, matrix.Color(255, 0, 0));
  //  screenSaver(10000, 6, 6, 7, 50);
  //  updateScreen();
  //  delay(10000);
  //  Reset();
  //  Serial.println("done");
  //  delay(1000);

  //  spot(7000, 5, 10, true);
  //  Reset();
  //  delay(1000);

  bling();

  //  sinWaveM(matrix.Color(255, 255, 255), 0, 2500, 25, 2);
  //  Reset();
  //  delay(2000);

  //  creditsPrint ("PhyXT", matrix.Color(255, 0, 0), 100, true, "Gears", matrix.Color(0, 255, 0), true, "GO", matrix.Color(0, 0, 255));
  //  String m1[] = {"1", "22", "333", "4444", "55555", "666666", "7777777", "88888888", "999999999"};
  /*
    int loopSize = sizeof(subteams) / sizeof(subteams[0]);
    Serial.println("Loop size: " + String(loopSize));
    uint16_t c1[] = {matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255), matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255),matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)};
    credits (subteams, c1, 0, 20, loopSize, true);
    Reset();
    delay(2500);*/

  //  audioBar(5000, 4);
  //  Reset();
  //  delay(2500);

  //  drawShip(1, 1, 1, WHITE);
  //  delay(10000);
  //  Reset();
  //  delay(1000);
}

void bling () {
  runBling(blingPrograms);
  Reset();
  blingSelect();
  delay(100);
}
