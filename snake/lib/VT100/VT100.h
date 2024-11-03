#include <Arduino.h>

#define sp(x) Serial.print(x)
#define spln(x) Serial.println(x)
#define sw(x) Serial.write(x)
#define esc() sw(0x1b)
#define spEsc(x) esc(), sp(x)

void setCursor(int x, int y);

void eraseCh(int x, int y);

void saveCursor();

void restoreCursor();

void cursorOff();

void cursorOn();

void clrScreen();

void screenWonB();

void eraseToEOL();

void eraseLine();