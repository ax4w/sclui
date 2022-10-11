#include <stdio.h>
#define SCLUI_C
#include "sclui.h"
#include <curses.h> 
#include <stdlib.h>

void mainScreen();

sclui_interactable_item *name = NULL;

void quit() {
  curs_set(1);
  endwin();
  exit(0);
}

void thrdScreen() { 
  char buff[100];
  snprintf(buff, 100, "Hello, %s", getTextboxText(name));
  sclui_screen *s3 = initScreen("3. Screen", 1, 1, 40, 20, KEY_UP, KEY_DOWN);
  sclui_item *i = createItem(buff, 10, 5);
  sclui_interactable_item *i1 = createButton("Quit", quit, 10, 6);
  centerItemX(s3,i);
  centerItemY(s3,i); 
  centerInteractableItemX(s3, i1);
  centerInteractableItemY(s3, i1);
  setInteractableItemY(i1, getInteractableItemY(i1)+1);
  addInteractableItem(s3, i1);
  addItem(s3, i);
  runScreen(s3);
}

void sndScreen() {

  sclui_screen *s2 = initScreen("Hello World", 3, 1, 40 , 20, KEY_UP, KEY_DOWN);
  name = createTextBox("Name", 15, 5, 20);
  sclui_interactable_item *i3 = createButton("Next", &thrdScreen, 15, 7);
  sclui_interactable_item *i4 = createButton("Quit", &quit, 15, 8);
  centerInteractableItemX(s2, name);
  centerInteractableItemX(s2,i3);
  centerInteractableItemX(s2,i4);
  addInteractableItem(s2, name); 
  addInteractableItem(s2, i3);
  addInteractableItem(s2, i4);
  runScreen(s2);
}

void mainScreen() {
  sclui_screen *s1 = initScreen("Example", 2,1, 45, 15, KEY_LEFT,KEY_RIGHT);
  sclui_item *example_text = createItem("This is a small demonstration application!", 1, 1);
  sclui_interactable_item *button1 = createButton("Next", &sndScreen, 5, 10);
  sclui_interactable_item *button2 = createButton("Quit", &quit, 30, 10);
  centerItemX(s1, example_text);
  addItem(s1,example_text);
  addInteractableItem(s1, button1);
  addInteractableItem(s1, button2);
  runScreen(s1);
}

int main() {
  WINDOW *w = initscr();
 if(w == NULL) exit(-1);
  setup();
  setConfig(0, 0);
  init_pair(2, COLOR_BLACK,COLOR_RED); //2 is always for buttons
  init_pair(1, COLOR_BLACK,COLOR_WHITE); //1 is for the window border
  mainScreen();  
}
