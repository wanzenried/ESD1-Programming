#include <Arduino.h>

// period time for game engine
#define TIMEPER 200
unsigned long gameTime;

int sign = 1;

// http://www.braun-home.net/michael/info/misc/VT100_commands.htm
// x,y in upper right corner
// x increasing down
// y increasing right

#define sp(x) Serial.print(x)
#define spln(x) Serial.println(x)
#define sw(x) Serial.write(x)
#define esc() sw(0x1b)
#define spEsc(x) esc(), sp(x)

void setCursor(int x, int y) {
  sw(0x1b);
  sp("[");
  sp(x);
  sp(";");
  sp(y);
  sp("H");
}

void eraseCh(int x, int y) {
  setCursor(x, y);
  sp(" ");
}

void saveCursor() {
  // ESC 7
  // restore ESC 8
  //esc();
  //sp("7");
  spEsc("7");
}

void restoreCursor() {
  // ESC 7
  // restore ESC 8
  //esc();
  //sp("8");
  spEsc("8");
}

void cursorOff() {
  //Esc [ ? 25 l
  esc();
  sp("[?25l");
}

void cursorOn() {
  //Esc [ ? 25 l
  esc();
  sp("[?25h");
}

void clrScreen() {
  /*
  *  ESC [ K           erase to end of line (inclusive)
 *  ESC [ 0 K         erase to end of line (inclusive)
 *  ESC [ 1 K         erase to beginning of line (inclusive)
 *  ESC [ 2 K         erase entire line (cursor doesn't move)
 *  ESC [ J           erase to end of screen (inclusive)
 *  ESC [ 0 J         erase to end of screen (inclusive)
 *  ESC [ 1 J         erase to beginning of screen (inclusive)
 *  ESC [ 2 J         erase entire screen (cursor doesn't move)
*/
  esc();
  sp("[2J");
}

void screenWonB() {
  /*
*  ESC [ ? 5 h       black characters on white screen mode
 *  ESC [ ? 5 l       white characters on black screen mode
*/
  esc();
  sp("[?5l");
}


void eraseToEOL() {
  /*
  Erasing:

 *  ESC [ K           erase to end of line (inclusive)
 *  ESC [ 0 K         erase to end of line (inclusive)
 *  ESC [ 1 K         erase to beginning of line (inclusive)
 *  ESC [ 2 K         erase entire line (cursor doesn't move)
 *  ESC [ J           erase to end of screen (inclusive)
 *  ESC [ 0 J         erase to end of screen (inclusive)
 *  ESC [ 1 J         erase to beginning of screen (inclusive)
 *  ESC [ 2 J         erase entire screen (cursor doesn't move)
*/
  spEsc("[K");  // ?
}

void eraseLine()
{
  spEsc("[2K");
}

// gameengine
int counter1 = 0;
int counter2 = 0;

void doGameEngine() {
  saveCursor();
  counter1 += sign;
  counter2 -= sign;
  //cursorOff();

  setCursor(10, 10);
  eraseToEOL();
  sp(counter1);

  setCursor(11, 10);
  eraseToEOL();
  sp(counter2);

  restoreCursor();
  //cursorOn();
}

void handleUser() {
  int k;
  // basicly cehck if keyboard input and process it
  // NB NB in gtkTerm and putty no <enter> is needed
  // keys are transmitted at once

  while (Serial.available()) {
    k = Serial.read();  // one byte 0..255
    switch (k) {
      case '+':
        sign = 1;
        break;
      case '-':
        sign = -1;
        break;
      case 'c':
        counter1 = counter2 = 0;
        break;
      default:;
    }
  }
}

/* -------oOo------- */
void setup() {

  Serial.begin(115200);
  Serial.println(__DATE__);
  Serial.println(__FILE__);
  delay(200);
  clrScreen();
  screenWonB();
  setCursor(0, 0);
  cursorOff();

  gameTime = millis() + TIMEPER;
}

unsigned long nextTime;
void loop() {
  nextTime = millis();
  if (gameTime <= nextTime) {
    doGameEngine();
    gameTime += TIMEPER;
  }
  handleUser();
}

// end of file  /JDN
