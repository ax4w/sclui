#ifndef SCLUI
#define SCLUI

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

typedef enum {BUTTON,TEXTBOX} type;

typedef struct {
  /*
     * General
  */
  char* text;
  int x;
  int y;
  type t;

  /*
     *Button
  */
  void(*action)();

  /*
    *Textbox
  */
  int text_length;
  char *usrInput;
  int max_text_length;
  int current_input_length;
} sclui_interactable_item;

typedef struct {
  char *text;
  int x;
  int y;
} sclui_item;

typedef struct {
  char *title;
  int title_length;
  
  int upKey;
  int downKey;

  int width;
  int height;
  
  sclui_interactable_item **interactable_items;
  int interactable_items_length;
  int interactable_items_current_length;

  sclui_item **items;
  int items_length;
  int items_current_length;
} sclui_screen; 


void runScreen(sclui_screen *screen);
void setConfig(int x, int y);
sclui_screen *initScreen(char *title,int title_length, int interactableItemsCount,int itemsCount, 
    int width, int height, int navKey1, int navKey2); 

sclui_interactable_item *createButton(char *text, void(*action)(),int x, int y);
sclui_interactable_item *createTextBox(char *text, int x, int y, int text_length, int max_text_length);

char *getTextboxText(sclui_interactable_item *textbox);
int getTextboxTextLength(sclui_interactable_item *textbox);

sclui_item* createItem(char *text, int x, int y);
void addInteractableItem(sclui_screen *screen, sclui_interactable_item *item); 
void addItem(sclui_screen *screen, sclui_item *item);

#endif

#define SCLUI_C
#ifdef SCLUI_C
sclui_config gConfig = {
    .posX = 0,
    .posY = 0
};

void setConfig(int x, int y) { 
  gConfig.posX = x;
  gConfig.posY = y;
}

sclui_screen *initScreen(char *title, int title_length, int interactableItemsCount, int itemsCount, int width, int height, int upKey, int downKey) {
  sclui_screen *s = (sclui_screen*)calloc(1,sizeof(sclui_screen));
  s->interactable_items = (sclui_interactable_item**)calloc(interactableItemsCount,sizeof(sclui_interactable_item*));
  s->interactable_items_length = interactableItemsCount;
  s->items = (sclui_item**)calloc(itemsCount,sizeof(sclui_item*));
  s->items_length = itemsCount;
  s->width = width;
  s->height = height;
  s->title = title;
  s->upKey = upKey;
  s->downKey = downKey;
  s->title_length = title_length;
  s->interactable_items_current_length = 0;
  s->items_current_length = 0;
  return s;
}


sclui_item *createItem(char *text, int x, int y) {
  sclui_item *s = (sclui_item*)calloc(1,sizeof(sclui_item));
  s->text = text;
  s->y = y;
  s->x = x;
  return s;
}

sclui_interactable_item *createTextBox(char *text, int x, int y,int text_length, int max_text_length) {
  sclui_interactable_item *s = (sclui_interactable_item*)calloc(1,sizeof(sclui_interactable_item));
  s->text = text;
  s->action = NULL;
  s->t = TEXTBOX;
  s->y = y;
  s->x = x;
  s->text_length = text_length;
  s->current_input_length = 0;
  s->max_text_length = max_text_length;
  s->usrInput = (char*)calloc(max_text_length,sizeof(char));
  return s;
}

char *getTextboxText(sclui_interactable_item *textbox) {
  return textbox->usrInput;
}

int getTextboxTextLength(sclui_interactable_item *textbox) {
  return textbox->current_input_length;
}

sclui_interactable_item *createButton(char *text, void(*action)(), int x, int y) {
  assert(action != NULL); 
  sclui_interactable_item *s = (sclui_interactable_item*)calloc(1,sizeof(sclui_interactable_item));
  s->text = text;
  s->x = x;
  s->y = y;
  s->t = BUTTON;
  s->action = action;
  return s;
}

void addItem(sclui_screen *screen, sclui_item *item) {
  assert(screen->items_current_length < screen->items_length);
  screen->items[(screen->items_current_length)++] = item;
}

void addInteractableItem(sclui_screen *screen, sclui_interactable_item *item) {
  assert(screen->interactable_items_current_length < screen->interactable_items_length);
  screen->interactable_items[(screen->interactable_items_current_length)++] = item;
}

void updateButton(sclui_interactable_item *button, int atr, int n) {
  if(atr == 0) { //off
    attroff(COLOR_PAIR(n));
  }else{
    attron(COLOR_PAIR(n));
  }
  move(gConfig.posY + button->y,gConfig.posY + button->x);
  addstr(button->text);
  move(gConfig.posY + button->y,gConfig.posY + button->x);
  attroff(COLOR_PAIR(n));
}



void updateTextbox(sclui_interactable_item *textbox, int atr, int n) {
   if(atr == 0) { //off
    attroff(COLOR_PAIR(n));
  }else{
    attron(COLOR_PAIR(n));
  }
  move(gConfig.posY + textbox->y,
      gConfig.posY + textbox->x);
  printw("%s:",textbox->text);
  attroff(COLOR_PAIR(n));
  move(gConfig.posY + textbox->y, gConfig.posX + textbox->x + textbox->text_length + 2);
  printw("%s",textbox->usrInput);
  move(gConfig.posY + textbox->y,
      gConfig.posX + textbox->x + textbox->text_length + 1 + textbox->current_input_length + 1);
}

int updateInteractable(sclui_screen *screen, int iidx, int mov) {
  if((mov == 0 && iidx < screen->interactable_items_current_length-1) || (mov == 1 && iidx > 0)) {
    switch(screen->interactable_items[iidx]->t) {
      case TEXTBOX:
        updateTextbox(screen->interactable_items[iidx],0,2);
        break;
      default:
        updateButton(screen->interactable_items[iidx], 0, 2);
    }
    iidx = mov == 0 ? iidx+1 : iidx-1;
    switch(screen->interactable_items[iidx]->t) {
      case TEXTBOX:
        curs_set(1);
        updateTextbox(screen->interactable_items[iidx], 1, 2);
        break;
      default:
        curs_set(0);
        updateButton(screen->interactable_items[iidx],1,2);
    }
    refresh();
  } 
  return iidx;
}

void printFrame(sclui_screen *screen) {
  //clear old screen
  clear();
  
  //set color to border color
  attron(COLOR_PAIR(1));
  move(gConfig.posY,gConfig.posX);

  //print 5 frame chars
  for(int i = 0; i < 5; i++) {
    addstr(H_FRAME);
  };

  //print title
  addstr(screen->title);
  
  //print the rest of the frame chars
  for(int i = 0; i <= (screen->width - screen->title_length - 5); i++) {
    addstr(H_FRAME);
  }
  move(gConfig.posY,gConfig.posX + screen->width);
  
  //print right vertical frame
  for(int i = 1; i <= screen->height+1; i++) {
    addstr(V_FRAME);
    move(gConfig.posY+i,gConfig.posX+screen->width);
  }

  move(gConfig.posY + screen->height,gConfig.posX);
  
  //print buttom
  for(int i = 1; i <= screen->width; i++) addstr(H_FRAME);
  move(gConfig.posY,gConfig.posX);
  
  //print left vertical frame
  for(int i = 1; i <= screen->height+1; i++) {
    addstr(V_FRAME);
    move(gConfig.posY+i,gConfig.posX);
  }
  attroff(COLOR_PAIR(1));
}

void runScreen(sclui_screen *screen) {
  int c, iidx = 0;
  printFrame(screen);

  //print non interactable items before interactable items
  if(screen->items_length > 0) {
    for(int i = 0; i < screen->items_current_length; i++) {
      move(gConfig.posY + screen->items[i]->y, gConfig.posX + screen->items[i]->x);
      addstr(screen->items[i]->text);
    }
  }

  //print interactable items
  if(screen->interactable_items_current_length > 0) {
    for(int i = 0; i < screen->interactable_items_current_length; i++) {
      switch(screen->interactable_items[i]->t) {
        case TEXTBOX:
          updateTextbox(screen->interactable_items[i], 0, 2);
          break;
        default:
          updateButton(screen->interactable_items[i],0,2);
          break;
      } 
    }

    //select first interactable item
    switch(screen->interactable_items[iidx]->t) {
      case TEXTBOX:
        curs_set(1);
        updateTextbox(screen->interactable_items[iidx], 1, 2);
        break;
      default:
        curs_set(0);
        updateButton(screen->interactable_items[iidx],1,2);
    }
  }
  refresh();
 
  while(1) {
    c  = getch();
   
    if(c == CONFIRM_KEY) {
      switch(screen->interactable_items[iidx]->t) {
        case TEXTBOX:
          //nothing todo yet
          break;
        default:
          (*screen->interactable_items[iidx]->action)();
          break;
      }
      
    }
    
    if(c == screen->downKey) {
      iidx = updateInteractable(screen, iidx, 0);
    }else if(c == screen->upKey) {
      iidx = updateInteractable(screen,iidx,1);
    }

    if(screen->interactable_items[iidx]->t == TEXTBOX) {
      if(c == KEY_BACKSPACE) {
        if(screen->interactable_items[iidx]->current_input_length >= 0) {
          screen->interactable_items[iidx]->usrInput[screen->interactable_items[iidx]->current_input_length--] = ' ';
          //if its less then 0, set it back to 0
          if(screen->interactable_items[iidx]->current_input_length < 0) screen->interactable_items[iidx]->current_input_length = 0;
          
          updateTextbox(screen->interactable_items[iidx], 1, 2);

        }
      }
      if(screen->interactable_items[iidx]->current_input_length < screen->interactable_items[iidx]->max_text_length &&
          (isalpha(c) || c == ' ')) {
        screen->interactable_items[iidx]->usrInput[screen->interactable_items[iidx]->current_input_length++] = c;
        updateTextbox(screen->interactable_items[iidx], 1, 2);
      }
    }
    refresh();
  }
}
#endif
