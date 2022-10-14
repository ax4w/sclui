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


void mainScreen() {
  color bt2c = {
    .b = COLOR_BLUE,
    .f = COLOR_YELLOW
  };

  color bt2fc = {
    .b = COLOR_RED,
    .f = COLOR_YELLOW
  };

   color cb2c = {
    .b = COLOR_MAGENTA,
    .f = COLOR_WHITE
  };

  color cb2fc = {
    .b = COLOR_CYAN,
    .f = COLOR_GREEN
  };
  color sc = {
    .b = COLOR_WHITE,
    .f = COLOR_BLACK
  };
  sclui_screen *s1 = initScreen("Example", 4,1, 45, 15, KEY_LEFT,KEY_RIGHT, &sc);
  sclui_item *example_text = createItem("This is a small demonstration application!", 1, 1);
  
  sclui_interactable_item *button1 = createButton("Quit", &doQuit, 20, 10,&bt2c,&bt2fc);
  sclui_interactable_item *button2 = createButton("Quit1", &doQuit, 30, 10,&bt2c,&bt2fc);

  name = createTextBox("Name", NULL, 8, 8,20,&bt2c,&bt2fc);

  sclui_interactable_item *checkbox1 = createCheckBox("Check",1,5,5,&cb2c,&cb2fc);
  centerItemX(s1, example_text);
  centerInteractableItemX(s1,checkbox1);
  addItem(s1,example_text);
  addInteractableItem(s1,name);
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
  mainScreen();  
}
