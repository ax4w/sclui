#define SCLUI_C
#include "sclui.h"
#include <curses.h> 
#include <stdlib.h>

void mainScreen();

sclui_interactable_item *name = NULL;

void i2f() {
  curs_set(1);
  endwin();
  exit(0);
}

void i1f() {

  sclui_screen *s2 = initScreen("Hello", 5, 2, 1, 41 , 30, KEY_UP, KEY_DOWN);
  sclui_item *i4 = createItem("World", 1, 1);
  name = createTextBox("Name", 10, 10, 4, 20);
  sclui_interactable_item *i3 = createButton("Back", &mainScreen, 20, 20);
  addInteractableItem(s2,name); 
  addInteractableItem(s2, i3);
  addItem(s2, i4);
  runScreen(s2);
}

void mainScreen() {
  sclui_screen *s1 = initScreen("Example",8, 2,1, 45, 15, KEY_LEFT,KEY_RIGHT);
  sclui_item *example_text = createItem("This is a small demonstration application!", 1, 1);
  sclui_interactable_item *button1 = createButton("Next", &i1f, 5, 10);
  sclui_interactable_item *button2 = createButton("Quit", &i2f, 30, 10);
  addItem(s1,example_text);
  addInteractableItem(s1, button1);
  addInteractableItem(s1, button2);
  runScreen(s1);
}

int main() {
  WINDOW *w = initscr();
  raw();
  noecho();
  keypad(stdscr,TRUE);
  if(w == NULL) exit(-1);
  setConfig(0, 0);
  start_color();
  init_pair(2, COLOR_BLACK,COLOR_RED); //2 is always for buttons
  init_pair(1, COLOR_BLACK,COLOR_WHITE); //1 is for the window border
  mainScreen();  
}
