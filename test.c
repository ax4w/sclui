#include <stdio.h>
#define SCLUI_C
#include "sclui.h"
#include <curses.h> 
#include <stdlib.h>
#include <stdbool.h>
void mainScreen();

sclui_interactable_item *name = NULL;
sclui_interactable_item *says = NULL;

//Quit action
void doQuit() {
  curs_set(1);
  endwin();
  exit(0);
}

//Example for an textbox filter
bool isOne(char c) {
  return c == '1';
}

void thrdScreen() { 
  char buff[100];
  snprintf(buff, 100, "%s says: %s", getTextboxText(name),getTextboxText(says));
  sclui_screen *s3 = initScreen("3. Screen", 1, 1, 40, 20, KEY_UP, KEY_DOWN);
  sclui_item *text = createItem(buff, 10, 5);
  sclui_interactable_item *quit = createButton("Quit", &doQuit, 10, 6);
  centerItemX(s3,text);
  centerItemY(s3,text); 
  centerInteractableItemX(s3, quit);
  centerInteractableItemY(s3, quit);
  setInteractableItemY(quit, getInteractableItemY(quit)+1);
  addInteractableItem(s3, quit);
  addItem(s3, text);
  runScreen(s3);
}

void sndScreen() {

  sclui_screen *s2 = initScreen("Hello World", 4, 1, 40 , 20, KEY_UP, KEY_DOWN);
  name = createTextBox("Name", NULL, 15, 5, 20);
  says = createTextBox("Says",&isOne, 15, 6, 20);
  sclui_interactable_item *next = createButton("Next", &thrdScreen, 15, 8);
  sclui_interactable_item *quit = createButton("Quit", &doQuit, 15, 9);
  centerInteractableItemX(s2, name);
  centerInteractableItemX(s2, says);
  centerInteractableItemX(s2,next);
  centerInteractableItemX(s2,quit);
  addInteractableItem(s2, name); 
  addInteractableItem(s2, says);
  addInteractableItem(s2, next);
  addInteractableItem(s2, quit);
  runScreen(s2);
}

void mainScreen() {
  sclui_screen *s1 = initScreen("Example", 3,1, 45, 15, KEY_LEFT,KEY_RIGHT);
  sclui_item *example_text = createItem("This is a small demonstration application!", 1, 1);
  sclui_interactable_item *button1 = createButton("Next", &sndScreen, 5, 10);
  sclui_interactable_item *button2 = createButton("Quit", &doQuit, 30, 10);
  sclui_interactable_item *checkbox1 = createCheckBox("Check",1,5,5);
  centerItemX(s1, example_text);
  centerInteractableItemX(s1,checkbox1);
  addItem(s1,example_text);
  addInteractableItem(s1,checkbox1);
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
