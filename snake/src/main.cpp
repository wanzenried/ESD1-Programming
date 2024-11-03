#include <Arduino.h>
#include <VT100.h>

// Prototypes:
void doGameEngine();
void handleUser();
void pushSnake(int x, int y);
void updateSnake();


// Definitions
#define snakeMaxLen 20

// period time for game engine
#define TIMEPER 200
unsigned long gameTime;

//Structs
typedef struct
{
  int x;
  int y;
} snakePart;

int dirX = 1;
int dirY = 0;

int snakeLen = 0;

snakePart snakeArr[snakeMaxLen];

void pushSnake(int x, int y) {
  snakePart s = {x, y};

  snakeArr[snakeLen] = s;

  snakeLen++;
}

void updateSnake() {
  snakeArr[0].x += dirX;
  snakeArr[0].y += dirY;

  for (int i = snakeLen-1; i > 0; i--)
  {
    snakeArr[i] = snakeArr[i-1];
  }
  
}




void doGameEngine() {
  saveCursor();
  /*
  counter1 += sign;
  counter2 -= sign;
  //cursorOff();

  setCursor(10, 10);
  eraseToEOL();
  sp(counter1);

  setCursor(11, 10);
  eraseToEOL();
  sp(counter2);*/
  updateSnake();

  setCursor(snakeArr[0].x,snakeArr[0].y);
  sp("#");

  eraseCh(snakeArr[snakeLen-1].x, snakeArr[snakeLen-1].y);
  restoreCursor();
  //cursorOn();
}

void handleUser() {
  int k;
  int tmp;
  // basicly cehck if keyboard input and process it
  // NB NB in gtkTerm and putty no <enter> is needed
  // keys are transmitted at once

  while (Serial.available()) {
    k = Serial.read();  // one byte 0..255
    switch (k) {
      case 'a':
        tmp = dirY;
        dirY = dirX;
        dirX = -1*tmp;
        break;
      case 'd':
        tmp = dirX;
        dirX = dirY;
        dirY = -1*tmp;
        break;
      case 'c':
        
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
  delay(500);
  clrScreen();
  screenWonB();
  setCursor(0, 0);
  cursorOff();

  gameTime = millis() + TIMEPER;

  for (int i = 0; i < 8; i++)
  {
    pushSnake(14,14);
  }
  
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
