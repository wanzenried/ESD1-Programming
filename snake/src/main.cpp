#include <Arduino.h>
#include <VT100.h>

// Prototypes:
void doGameEngine();
void handleUser();
void pushSnake(int x, int y);
void updateSnake();
bool snakeCollision(int x, int y);
void resetSnake(int x, int y);

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

//check if specific coordinate (of the snakes head) collides with the snake
//Does not check the head of the snake, as the snake head cannot collide with itself
bool snakeCollision(int x, int y){
  for (int i = 1; i < snakeLen; i++)
  {
    if (snakeArr[i].x == x && snakeArr[i].y == y)
    {
      return true;
    }
  }
  //if this part of the code is reached, no part of the snake is touching the supplied coords
  return false;
}

//resets the position of the snake to the given coordinates
//Also resets the length of the snake back to 1 and clears the screen
void resetSnake(int x, int y)
{
  snakeArr[0].x = x;
  snakeArr[0].y = y;

  snakeLen = 1;

  clrScreen();
}



void doGameEngine() {
  saveCursor();

  //Remove last part of the snakes tail
  eraseCh(snakeArr[snakeLen-1].x, snakeArr[snakeLen-1].y);

  updateSnake();

  //print the new location of the head
  setCursor(snakeArr[0].x,snakeArr[0].y);
  sp("#");

  restoreCursor();
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
