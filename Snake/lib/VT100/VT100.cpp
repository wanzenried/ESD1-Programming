#include <VT100.h>

// http://www.braun-home.net/michael/info/misc/VT100_commands.htm
// x,y in upper right corner
// x increasing down
// y increasing right

// Based on code written by JDN:
// https://www.moodle.aau.dk/pluginfile.php/3283793/mod_resource/content/1/vt100_5.ino

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