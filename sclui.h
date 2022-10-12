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

typedef enum {BUTTON,TEXTBOX, CHECKBOX} type;

typedef struct {
  /*
     * General
  */
  char* text;
  int text_length;
  int x;
  int y;
  type t;

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

typedef struct {
  char *text;
  int text_length;
  int x;
  int y;
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
    int width, int height, int navKey1, int navKey2); 
void setup();

/*
===================Interactables=========================   
*/

//Button
sclui_interactable_item *createButton(char *text, void(*action)(),int x, int y);

//Textbox
sclui_interactable_item *createTextBox(char *text, bool(*filter)(char), int x, int y, int max_text_length);
char *getTextboxText(sclui_interactable_item *textbox);
int getTextboxTextLength(sclui_interactable_item *textbox);

//Checkbox
sclui_interactable_item *createCheckBox(char *text, int defaultValue , int x, int y);
int getCheckBoxValue(sclui_interactable_item *checkbox);
int getCheckBoxDefaultValue(sclui_interactable_item *checkbox);

//General
void setInteractableItemX(sclui_interactable_item *item, int x);
void setInteractableItemY(sclui_interactable_item *item, int y);

void centerInteractableItemX(sclui_screen *screen, sclui_interactable_item *item);
void centerInteractableItemY(sclui_screen *screen, sclui_interactable_item *item);

int getInteractableItemX(sclui_interactable_item *item);
int getInteractableItemY(sclui_interactable_item *item);

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

void centerItemX(sclui_screen *screen, sclui_item *item);
void centerItemY(sclui_screen *screen, sclui_item *item);

int getItemX(sclui_item *item);
int getItemY(sclui_item *item);

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

void setup() {
  raw();
  noecho();
  start_color();
  keypad(stdscr,TRUE);
}

int getTextLength(char *s) {
  int i = 0;
  while(*s++ != '\0') {
    i++;
  }
  return i;
}

/*
  *Screen
*/
sclui_screen *initScreen(char *title, int interactableItemsCount, int itemsCount, int width, int height, int upKey, int downKey) {
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
  s->title_length = getTextLength(title);
  s->interactable_items_current_length = 0;
  s->items_current_length = 0;
  return s;
}

int getMaxItemsLength(sclui_screen *screen) {
  return screen->items_length;
}

int getCurrentItemsLength(sclui_screen *screen) {
  return screen->items_current_length;
}

int getCurrentInteractableItemsLength(sclui_screen *screen) {
  return screen->interactable_items_current_length;
}

int getMaxInteractableItemsLength(sclui_screen *screen) {
  return screen->interactable_items_length;
}

sclui_interactable_item *getInteractableItem(sclui_screen *screen, int i) {
  return screen->interactable_items[i];
}

sclui_item *getItem(sclui_screen *screen, int i) {
  return screen->items[i];
}
/*
  Item
*/
sclui_item *createItem(char *text, int x, int y) {
  sclui_item *s = (sclui_item*)calloc(1,sizeof(sclui_item));
  s->text = text;
  s->text_length = getTextLength(text);
  printw("%d",s->text_length);
  s->y = y;
  s->x = x;
  return s;
}

char *getItemText(sclui_item *item) {
  return item->text;
}

/*
  *Interactable Items
*/
/*
  *Checkbox
*/
sclui_interactable_item *createCheckBox(char *text, int defaultValue, int x, int y) {
  sclui_interactable_item *s = (sclui_interactable_item*)calloc(1,sizeof(sclui_interactable_item));
  s->text = text;
  s->checkbox_checkBoxVal = defaultValue;
  s->text_length = getTextLength(text);
  s->x = x;
  s->y = y;
  s->t = CHECKBOX;
}

int getCheckBoxValue(sclui_interactable_item *checkbox) {
  return checkbox->checkbox_checkBoxVal;
}
int getCheckBoxDefaultValue(sclui_interactable_item *checkbox) {
  return checkbox->checkbox_defaultVal;
}

int flipCheckBoxValue(sclui_interactable_item *checkbox) {
  return getCheckBoxValue(checkbox) == 0 ? 1 : 0;
}

/*
   *Textbox
*/
sclui_interactable_item *createTextBox(char *text, bool(*filter)(char), int x, int y, int max_text_length) {
  sclui_interactable_item *s = (sclui_interactable_item*)calloc(1,sizeof(sclui_interactable_item));
  s->text = text;
  s->t = TEXTBOX;
  s->y = y;
  s->x = x;
  s->textbox_filter = filter;
  s->text_length = getTextLength(text);
  s->textbox_current_input_length = 0;
  s->textbox_max_text_length = max_text_length;
  s->textbox_usrInput = (char*)calloc(max_text_length,sizeof(char));
  return s;
}

char *getTextboxText(sclui_interactable_item *textbox) {
  return textbox->textbox_usrInput;
}

int getTextboxTextLength(sclui_interactable_item *textbox) {
  return textbox->textbox_current_input_length;
}

int getTextboxCurrentLength(sclui_interactable_item *textbox) {
  return textbox->textbox_current_input_length;
}

int getTextboxMaxTextLength(sclui_interactable_item *textbox) {
  return textbox->textbox_max_text_length;
}

char *getTextboxUserInput(sclui_interactable_item *textbox) {
  return textbox->textbox_usrInput;
}

/*
   * Button
*/
sclui_interactable_item *createButton(char *text, void(*action)(), int x, int y) {
  assert(action != NULL); 
  sclui_interactable_item *s = (sclui_interactable_item*)calloc(1,sizeof(sclui_interactable_item));
  s->text = text;
  s->x = x;
  s->text_length = getTextLength(text);
  s->y = y;
  s->t = BUTTON;
  s->button_action = action;
  return s;
}


/*
  *Helper function general for interactable items and items
*/
int getInteractableItemX(sclui_interactable_item *item) {return item->x;}
int getInteractableItemY(sclui_interactable_item *item) {return item->y;}

int getItemX(sclui_item *item) {return item->x;}
int getItemY(sclui_item *item) {return item->y;}

void setInteractableItemX(sclui_interactable_item *item, int x) { item->x = x;}
void setInteractableItemY(sclui_interactable_item *item, int y) { item->y = y;}
void setItemX(sclui_item *item, int x) {item->x = x;}
void setItemY(sclui_item *item, int y) {item->y = y;}


void centerInteractableItemX(sclui_screen *screen, sclui_interactable_item *item) {
  switch(item->t) {
    case TEXTBOX:
      setInteractableItemX(item,(screen->width/2) - ((item->text_length + item->textbox_max_text_length) / 2)-2);
      break;
    default:
      setInteractableItemX(item,(screen->width / 2) - (item->text_length / 2)-2);
      break;
  }
}

void centerItemX(sclui_screen *screen, sclui_item *item) {
  setItemX(item,(screen->width / 2) - (item->text_length / 2));
}

void centerItemY(sclui_screen * screen, sclui_item *item) {
  setItemY(item,(screen->height / 2));
}

void centerInteractableItemY(sclui_screen * screen, sclui_interactable_item *item) {
  setInteractableItemY(item,(screen->height / 2));
}

void addItem(sclui_screen *screen, sclui_item *item) {
  assert(screen->items_current_length < screen->items_length);
  screen->items[(screen->items_current_length)++] = item;
}

void addInteractableItem(sclui_screen *screen, sclui_interactable_item *item) {
  assert(screen->interactable_items_current_length < screen->interactable_items_length);
  screen->interactable_items[(screen->interactable_items_current_length)++] = item;
}

/*
  *Update functions
*/

void updateCheckbox(sclui_interactable_item *checkbox, int atr, int n) {
  if(atr == 0) { //off
    attroff(COLOR_PAIR(n));
  }else{
    attron(COLOR_PAIR(n));
  }
  move(
      gConfig.posY + getInteractableItemY(checkbox),
      gConfig.posY + getInteractableItemX(checkbox)
  );
  printw("| %s: %c |", checkbox->text,getCheckBoxValue(checkbox) == 0 ? 'O' : 'X');
  move(
      gConfig.posY + getInteractableItemY(checkbox),
      gConfig.posY + getInteractableItemX(checkbox)
  );
  attroff(COLOR_PAIR(n));
}

void updateButton(sclui_interactable_item *button, int atr, int n) {
  if(atr == 0) { //off
    attroff(COLOR_PAIR(n));
  }else{
    attron(COLOR_PAIR(n));
  }
  move(
      gConfig.posY + getInteractableItemY(button),
      gConfig.posY + getInteractableItemX(button)
  );
  printw("| %s |",button->text);
  move(
      gConfig.posY + getInteractableItemY(button),
      gConfig.posY + getInteractableItemX(button)
  );
  attroff(COLOR_PAIR(n));
}


void updateTextbox(sclui_interactable_item *textbox, int atr, int n) {
   if(atr == 0) { //off
    attroff(COLOR_PAIR(n));
  }else{
    attron(COLOR_PAIR(n));
  }
  move(
      gConfig.posY + getInteractableItemY(textbox),
      gConfig.posY + getInteractableItemX(textbox)
  );
  printw("| %s: ",textbox->text);
  attroff(COLOR_PAIR(n));
  move(
      gConfig.posY + getInteractableItemY(textbox), 
      gConfig.posX + getInteractableItemX(textbox) + textbox->text_length + 4
  );
  printw("%s ",getTextboxUserInput(textbox));
  move(
      gConfig.posY + getInteractableItemY(textbox) , 
      gConfig.posX  + getInteractableItemX(textbox) + textbox->text_length+ 5 
        + getTextboxMaxTextLength(textbox)
  );
  if(atr != 0) attron(COLOR_PAIR(n));
  addstr("|");
  attroff(COLOR_PAIR(n));
  move(
      gConfig.posY + getInteractableItemY(textbox),
      gConfig.posX + getInteractableItemX(textbox) + textbox->text_length + 1 
        + getTextboxCurrentLength(textbox) + 3
  );
}

int updateInteractable(sclui_screen *screen, int iidx, int mov) {
  if((mov == 0 && iidx < getCurrentInteractableItemsLength(screen)-1) || (mov == 1 && iidx > 0)) {
    switch(getInteractableItem(screen,iidx)->t) {
      case TEXTBOX:
        updateTextbox(getInteractableItem(screen,iidx),0,2);
        break;
      case CHECKBOX:
        updateCheckbox(getInteractableItem(screen,iidx),0,2);
        break;
      default:
        updateButton(getInteractableItem(screen,iidx), 0, 2);
    }
    iidx = mov == 0 ? iidx+1 : iidx-1;
    switch(getInteractableItem(screen,iidx)->t) {
      case TEXTBOX:
        curs_set(1);
        updateTextbox(getInteractableItem(screen,iidx), 1, 2);
        break;
      case CHECKBOX:
        curs_set(0);
        updateCheckbox(getInteractableItem(screen,iidx),1,2);
        break;
      default:
        curs_set(0);
        updateButton(getInteractableItem(screen,iidx),1,2);
    }
    refresh();
  } 
  return iidx;
}

bool defaultTextBoxFilter(char c) {
  return isalpha(c) || c == ' ';
}

void printFrame(sclui_screen *screen) {
  //clear old screen
  clear();
  
  //set color to border color
  attron(COLOR_PAIR(1));
  move(
      gConfig.posY,
      gConfig.posX
  );

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
  move(
      gConfig.posY,
      gConfig.posX + screen->width
  );
  
  //print right vertical frame
  for(int i = 1; i <= screen->height+1; i++) {
    addstr(V_FRAME);
    move(
        gConfig.posY+i,
        gConfig.posX+screen->width
    );
  }

  move(
      gConfig.posY + screen->height,
      gConfig.posX
  );
  
  //print buttom
  for(int i = 1; i <= screen->width; i++) addstr(H_FRAME);
  move(
      gConfig.posY,
      gConfig.posX
  );
  
  //print left vertical frame
  for(int i = 1; i <= screen->height+1; i++) {
    addstr(V_FRAME);
    move(
        gConfig.posY+i,
        gConfig.posX
    );
  }
  attroff(COLOR_PAIR(1));
}

void runScreen(sclui_screen *screen) {
  int c, iidx = 0;
  printFrame(screen);

  //print non interactable items before interactable items
  if(getCurrentItemsLength(screen) > 0) {
    for(int i = 0; i < getCurrentItemsLength(screen); i++) {
      move(
          gConfig.posY + getItem(screen,i)->y, 
          gConfig.posX + getItem(screen,i)->x
      );
      addstr(getItemText(getItem(screen,i)));
    }
  }

  //print interactable items
  if(getCurrentInteractableItemsLength(screen) > 0) {
    for(int i = 0; i < getCurrentInteractableItemsLength(screen); i++) {
      switch(getInteractableItem(screen,i)->t) {
        case TEXTBOX:
          updateTextbox(getInteractableItem(screen,i), 0, 2);
          break;
        case CHECKBOX:
          updateCheckbox(getInteractableItem(screen,iidx),0,2);
          break;
        default:
          updateButton(getInteractableItem(screen,i),0,2);
          break;
      } 
    }

    //select first interactable item
    switch(getInteractableItem(screen,iidx)->t) {
      case TEXTBOX:
        curs_set(1);
        updateTextbox(getInteractableItem(screen,iidx), 1, 2);
        break;
      case CHECKBOX:
        curs_set(0);
        updateCheckbox(getInteractableItem(screen,iidx),1,2);
        break;
      default:
        curs_set(0);
        updateButton(getInteractableItem(screen,iidx),1,2);
    }
  }
  refresh();
 
  while(1) {
    c  = getch();
   
    if(c == CONFIRM_KEY) {
      switch(getInteractableItem(screen,iidx)->t) {
        case TEXTBOX:
          //nothing todo yet
          break;
        case CHECKBOX:
          getInteractableItem(screen,iidx)->checkbox_checkBoxVal = flipCheckBoxValue(getInteractableItem(screen,iidx));
          updateCheckbox(getInteractableItem(screen,iidx),1,2);
          break;
        default:
          (*getInteractableItem(screen,iidx)->button_action)();
          break;
      }
      
    }
    
    if(c == screen->downKey) {
      iidx = updateInteractable(screen, iidx, 0);
    }else if(c == screen->upKey) {
      iidx = updateInteractable(screen,iidx,1);
    }

    if(getInteractableItem(screen,iidx)->t == TEXTBOX) {
      if(c == KEY_BACKSPACE) {
        if(getTextboxCurrentLength(getInteractableItem(screen,iidx)) >= 0) {
          getTextboxUserInput(getInteractableItem(screen,iidx))
            [getInteractableItem(screen,iidx)->textbox_current_input_length--] = ' ';
          //if its less then 0, set it back to 0
          if(getTextboxCurrentLength(getInteractableItem(screen,iidx))  < 0) 
            getInteractableItem(screen,iidx)->textbox_current_input_length = 0;
          
          updateTextbox(getInteractableItem(screen,iidx), 1, 2);

        }
      }
      if(getTextboxCurrentLength(getInteractableItem(screen,iidx)) < getTextboxMaxTextLength(getInteractableItem(screen,iidx))) {
        if((getInteractableItem(screen,iidx)->textbox_filter == NULL 
            && defaultTextBoxFilter(c)) 
            || (getInteractableItem(screen,iidx)->textbox_filter != NULL 
            && (*(getInteractableItem(screen,iidx)->textbox_filter))(c))) {
          getTextboxUserInput(getInteractableItem(screen,iidx))[getInteractableItem(screen,iidx)->textbox_current_input_length++] = c;
          updateTextbox(getInteractableItem(screen,iidx), 1, 2);
        }
      }
    }
    refresh();
  }
}
#endif
