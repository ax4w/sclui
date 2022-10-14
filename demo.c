#include <stdio.h>
#define SCLUI_C
#include "sclui.h"
#include <curses.h> 
#include <stdlib.h>
#include <stdbool.h>
void mainScreen();

//Quit action


void mainScreen() {
  color buttonColor = {
    .b = COLOR_WHITE,
    .f = COLOR_BLACK
  };

  color buttonColorFocus = {
    .b = COLOR_RED,
    .f = COLOR_BLACK
  };

   color checkboxColor = {
    .b = COLOR_WHITE,
    .f = COLOR_BLACK
  };

  color checkboxFocusColor = {
    .b = COLOR_GREEN,
    .f = COLOR_BLACK
  };
  color screenColor = {
    .b = COLOR_WHITE,
    .f = COLOR_BLACK
  };
  sclui_screen *s1 = initScreen("Example", 4,1, 45, 15, KEY_LEFT,KEY_RIGHT, &screenColor);
  sclui_item *example_text = createItem("This is a small demonstration application!", 1, 1);
  
  //doQuit is a default function from SCLUI
  sclui_interactable_item *button1 = createButton("Quit1", &doQuit, 30, 11,&buttonColor,&buttonColorFocus);
  sclui_interactable_item *button2 = createButton("Quit2", &doQuit, 30, 13,&buttonColor,&buttonColorFocus);

  sclui_interactable_item *name = createTextBox("Name", NULL, 8, 5,8,&buttonColor,&buttonColorFocus);

  sclui_interactable_item *checkbox1 = createCheckBox("Check",1,5,9,&checkboxColor,&checkboxFocusColor);
  addInteractableItem(s1,name);
  addInteractableItem(s1,checkbox1);
  addInteractableItem(s1, button1);
  addInteractableItem(s1, button2);
  addItem(s1,example_text);
  checkbox1->center(checkbox1,X);
  example_text->center(example_text,X);
  name->center(name,X);
  button1->center(button1,X);
  button2->center(button2,X);
 
  
  runScreen(s1);
}

int main() {
  WINDOW *w = initscr();
  if(w == NULL) exit(-1);
  setup();
  setConfig(0, 0);
  mainScreen();  
}
