#include <Arduino.h>
#include <VT100.h>

// period time for game engine
#define TIMEPER 200
unsigned long gameTime;

int sign = 1;







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
