#pragma once

#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#ifndef H_FRAME
#define H_FRAME "="
#endif

#ifndef V_FRAME 
#define V_FRAME "|"
#endif

#ifndef CONFIRM_KEY
#define CONFIRM_KEY ' '
#endif

typedef struct {
  int posX;
  int posY;
} sclui_config;

typedef enum {BUTTON,TEXTBOX, CHECKBOX} type;
typedef enum {X,Y,XY} axsis;

typedef struct {
  int b;
  int f;
} color;

typedef struct sclui_interactable_item_struct{
  /*
     * General
  */
  char* text;
  int text_length;
  int x;
  int y;
  type t;

  void(*update)(struct sclui_interactable_item_struct *item,int s);
  void(*center)(struct sclui_interactable_item_struct *item,axsis a);
  
  
  struct sclui_interactable_item_struct *self;

  void* screen;
  color *bcolor;
  color *fcolor;
  int cp;
  int cpf;
  bool enabled;

  /*
     *Button
  */
  void(*button_action)();


  /*
    *Textbox
  */
  char *textbox_usrInput;
  bool (*textbox_filter)(char);
  int textbox_max_text_length;
  int textbox_current_input_length;

  /*
    *Checkbox
  */
  int checkbox_checkBoxVal;
  int checkbox_defaultVal;
  
} sclui_interactable_item;

typedef struct sclui_item_struct{
  char *text;
  int text_length;
  int x;
  int y;

  struct sclui_item_struct *self;
  void(*center)(struct sclui_item_struct *i, axsis a);
  
  void* screen;

} sclui_item;

typedef struct {
  /*
    *General
  */
  char *title;
  int title_length;
  
  int upKey;
  int downKey;

  int width;
  int height;

  color *color;
  
  /*
    *Interactable Items
  */
  sclui_interactable_item **interactable_items;
  int interactable_items_length;
  int interactable_items_current_length;

  /*
    *Items
  */
  sclui_item **items;
  int items_length;
  int items_current_length;
} sclui_screen; 


/*
====================Screen===============================
*/
void runScreen(sclui_screen *screen);
void setConfig(int x, int y);
sclui_screen *initScreen(char *title, int interactableItemsCount,int itemsCount, 
    int width, int height, int navKey1, int navKey2,color *color); 
void setup();
sclui_interactable_item *getInteractableItemByText(sclui_screen *screen, char *name);
void updateCurrentScreen();
void freeScreen(sclui_screen *screen);
void doQuit();
sclui_screen *currentScreen = NULL;

/*
===================Interactables=========================   
*/

#define createButton(text,action,x,y,color,focus_color) \
  createInteractableItem(text,action,NULL,BUTTON,x,y,0,0,color,focus_color,3,4);

#define createTextBox(text,filter,x,y,max_length,color,focus_color) \
  createInteractableItem(text,NULL,filter,TEXTBOX,x,y,max_length,0,color,focus_color,5,6);

#define createCheckBox(text,defaultValue,x,y,color,focus_color) \
  createInteractableItem(text,NULL,NULL,CHECKBOX,x,y,0,defaultValue,color,focus_color,7,8)

sclui_interactable_item *current;


//Textbox
char *getTextboxText(sclui_interactable_item *textbox);
int getTextboxTextLength(sclui_interactable_item *textbox);
void *setTextBoxUserInput(struct sclui_interactable_item_struct *textbox, char* text);
char *getTextboxUserInput(struct sclui_interactable_item_struct *textbox);

//Checkbox
int getCheckBoxValue(sclui_interactable_item *checkbox);
int getCheckBoxDefaultValue(sclui_interactable_item *checkbox);

//General

void updateColor(sclui_interactable_item *item, color *c);

void setInteractableItemX(sclui_interactable_item *item, int x);
void setInteractableItemY(sclui_interactable_item *item, int y);

int getInteractableItemX(sclui_interactable_item *item);
int getInteractableItemY(sclui_interactable_item *item);
sclui_interactable_item *getInteractableItem(sclui_screen *screen, int i);
//add
void addInteractableItem(sclui_screen *screen, sclui_interactable_item *item);


/*
==================Items===================================
*/

//create
sclui_item* createItem(char *text, int x, int y);

//helper
void addItem(sclui_screen *screen, sclui_item *item);

void setItemX(sclui_item *item, int x);
void setItemY(sclui_item *item, int y);

int getItemX(sclui_item *item);
int getItemY(sclui_item *item);

