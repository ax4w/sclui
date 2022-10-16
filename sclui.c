#include "sclui.h"


/*
  *GENERAL
*/
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

/*
  * MISC
*/
bool defaultTextBoxFilter(char c) {
  return isalpha(c) || c == ' ';
}

void doQuit() {
  curs_set(1);
  freeScreen(currentScreen);
  endwin();
  exit(0);
}

int getTextLength(char *s) {
  int i = 0;
  while(*s++ != '\0') {
    i++;
  }
  return i;
}

/*
  *INTERACTABLE ITEMS FUNCTIONS
*/

int getTextboxTextLength(struct sclui_interactable_item_struct *textbox) {
  return textbox->textbox_current_input_length;
}

int getTextboxCurrentLength(struct sclui_interactable_item_struct *textbox) {
  return textbox->textbox_current_input_length;
}

int getTextboxMaxTextLength(struct sclui_interactable_item_struct *textbox) {
  return textbox->textbox_max_text_length;
}

char *getTextboxUserInput(struct sclui_interactable_item_struct *textbox) {
  return textbox->textbox_usrInput;
}

void *setTextBoxUserInput(struct sclui_interactable_item_struct *textbox, char* text) {
  textbox->textbox_usrInput = text;
  textbox->textbox_current_input_length = getTextLength(text);
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

int getInteractableItemX(sclui_interactable_item *item) {return item->x;}
int getInteractableItemY(sclui_interactable_item *item) {return item->y;}

void setInteractableItemX(sclui_interactable_item *item, int x) { item->x = x;}
void setInteractableItemY(sclui_interactable_item *item, int y) { item->y = y;}

void centerInteractableItem(sclui_interactable_item *i, axsis a) {
  switch(a) {
    case X:
      switch(i->t) {
        case TEXTBOX:
          setInteractableItemX(i,(((sclui_screen*)i->screen)->width/2) - ((i->text_length + i->textbox_max_text_length) / 2)-2);
          break;
        case CHECKBOX:
          setInteractableItemX(i,(((sclui_screen*)i->screen)->width / 2) - (i->text_length / 2)-3);
          break;
        default:
          setInteractableItemX(i,(((sclui_screen*)i->screen)->width / 2) - (i->text_length / 2)-2);
          break;
      }
      break;
    case Y:
      setInteractableItemY(i,(((sclui_screen*)i->screen)->height / 2));
      break;
    default:
      centerInteractableItem(i,X);
      centerInteractableItem(i,Y);
      break;
  }
}

/*
  *SCREEN FUNCTIONS
*/

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

sclui_interactable_item *getInteractableItemByText(sclui_screen *screen, char *text) {
  for(int i = 0; i < getCurrentInteractableItemsLength(screen); i++) {
    if(getInteractableItem(screen,i)->text == text) {
      return getInteractableItem(screen,i);
    }
  }
  return NULL;
}

void freeScreen(sclui_screen *screen) {
  int il = getCurrentItemsLength(screen);
  int iil = getCurrentInteractableItemsLength(screen);
  for(int i = 0; i < il; i++) {
    free(getItem(screen,i));
  }
  for(int i = 0; i < iil; i++) {
    free(getInteractableItem(screen,i));
  }
  free(screen);
}

/*
  * ITEM FUNCTIONS
*/


char *getItemText(sclui_item *item) {
  return item->text;
}

int getItemX(sclui_item *item) {return item->x;}
int getItemY(sclui_item *item) {return item->y;}

void setItemX(sclui_item *item, int x) {item->x = x;}
void setItemY(sclui_item *item, int y) {item->y = y;}

void centerItem(sclui_item *i, axsis a) {
  switch(a) {
    case X:
      setItemX(i,(((sclui_screen*)i->screen)->width / 2) - (i->text_length / 2));
      break;
    case Y:
      setItemY(i,(((sclui_screen*)i->screen)->height / 2));
      break;
    default:
      centerItem(i,X);
      centerItem(i,Y);
      break;
  }
}


/*
  *UPDATE INTERACTABLE - MISC
*/
void setColor(sclui_interactable_item *i, int n) {
  switch (n) {
    case 1:
      if(i->bcolor != NULL) {
        init_pair(
          i->cp,
          i->bcolor->f,
          i->bcolor->b
        );
        attron(COLOR_PAIR(i->cp));
      }else{
        attroff(COLOR_PAIR(i->cp));
      }
      break;
    case 2:
      if(i->fcolor != NULL) {
          init_pair(
            i->cpf,
            i->fcolor->f,
            i->fcolor->b
          );
          attron(COLOR_PAIR(i->cpf));
      }else{
          attroff(COLOR_PAIR(i->cpf));
      }
      break;
  }
}


/*
  *UPDATE INTERACTABLE
*/
void updateCheckbox(sclui_interactable_item *checkbox, int n) {
  curs_set(0);
  setColor(checkbox,n);
  move(
      gConfig.posY + getInteractableItemY(checkbox),
      gConfig.posY + getInteractableItemX(checkbox)
  );
  printw("[ %s: (%c) ]", checkbox->text,getCheckBoxValue(checkbox) == 0 ? ' ' : 'X');
  move(
      gConfig.posY + getInteractableItemY(checkbox),
      gConfig.posY + getInteractableItemX(checkbox)
  );
  
}

void updateButton(sclui_interactable_item *button, int n) {
  curs_set(0);
  setColor(button,n);
  move(
      gConfig.posY + getInteractableItemY(button),
      gConfig.posY + getInteractableItemX(button)
  );
  printw("[ %s ]",button->text);
  move(
      gConfig.posY + getInteractableItemY(button),
      gConfig.posY + getInteractableItemX(button)
  );
}


void updateTextbox(sclui_interactable_item *textbox, int n) {
  curs_set(1);
  setColor(textbox,n);
  move(
      gConfig.posY + getInteractableItemY(textbox),
      gConfig.posY + getInteractableItemX(textbox)
  );
  printw("[ %s: ",textbox->text);
  for(int i = 0; i <= getTextboxMaxTextLength(textbox); i++) printw(" ");
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
  addstr("]");
  move(
      gConfig.posY + getInteractableItemY(textbox),
      gConfig.posX + getInteractableItemX(textbox) + textbox->text_length + 1 
        + getTextboxCurrentLength(textbox) + 3
  );
}


/*
  *GENERAL UPDATE
*/
int updateInteractable(int iidx, int mov) {
  if((mov == 0 && iidx < getCurrentInteractableItemsLength(currentScreen)-1) || (mov == 1 && iidx > 0)) {
    sclui_interactable_item *i = getInteractableItem(currentScreen,iidx);
    (*(i->update))(i,1);
    iidx = mov == 0 ? iidx+1 : iidx-1;
    i = getInteractableItem(currentScreen,iidx);
    (*(i->update))(i,2);
    refresh();
  } 
  return iidx;
}



/*
  *RENDER SCREEN
*/
void printFrame() {
  
  clear();
  //set color to border color
  init_pair(1,currentScreen->color->f,currentScreen->color->b);
  attron(COLOR_PAIR(1));
  
  move(gConfig.posY, gConfig.posX);

  //print 5 frame chars
  for(int i = 0; i < 5; i++) {
    addstr(H_FRAME);
  };

  //print title
  addstr(currentScreen->title);
  
  //print the rest of the frame chars
  for(int i = 0; i <= (currentScreen->width - currentScreen->title_length - 5); i++) {
    addstr(H_FRAME);
  }
  move(gConfig.posY,gConfig.posX + currentScreen->width);
  
  //print right vertical frame
  for(int i = 1; i <= currentScreen->height+1; i++) {
    addstr(V_FRAME);
    move(gConfig.posY + i,gConfig.posX + currentScreen->width);
  }

  move(gConfig.posY + currentScreen->height, gConfig.posX);
  
  //print buttom
  for(int i = 1; i <= currentScreen->width; i++) addstr(H_FRAME);
  move(gConfig.posY, gConfig.posX);
  
  //print left vertical frame
  for(int i = 1; i <= currentScreen->height+1; i++) {
    addstr(V_FRAME);
    move(gConfig.posY+i, gConfig.posX);
  }
  attroff(COLOR_PAIR(1));
}

void showItems() {
  if(getCurrentItemsLength(currentScreen) > 0) {
    for(int i = 0; i < getCurrentItemsLength(currentScreen); i++) {
      move(
          gConfig.posY + getItem(currentScreen,i)->y, 
          gConfig.posX + getItem(currentScreen,i)->x
      );
      char* t = getItemText(getItem(currentScreen,i));
      int yOffset = 1;
      while(*t) {
        if(*t == '\n') {
          break;
        }
        printw("%c",*t++);
      }
    }
  }

  if(getCurrentInteractableItemsLength(currentScreen) > 0) {
    for(int i = 0; i < getCurrentInteractableItemsLength(currentScreen); i++) {
      getInteractableItem(currentScreen,i)->update(getInteractableItem(currentScreen,i),1);
    }
    getInteractableItem(currentScreen,0)->update(getInteractableItem(currentScreen,0),2);
  }
}
int iidx = 0;

void updateCurrentScreen() {
  printFrame();
  showItems();
  refresh();
  iidx = 0;
  current = getInteractableItem(currentScreen,iidx);
}

void runScreen(sclui_screen *screen) {
  currentScreen = screen;
  
  int c;
  updateCurrentScreen();

  while(1) {
    c  = getch();
    current = getInteractableItem(screen,iidx);

    if(current->enabled) {
      switch (c) {
        case CONFIRM_KEY:
          switch (current->t)
          {
          case TEXTBOX:
            if(c == ' ') goto txt;
            break;
          case CHECKBOX:
            current->checkbox_checkBoxVal = flipCheckBoxValue(getInteractableItem(screen,iidx));
            current->update(current,2);
            break;
          default:
            (*(current->button_action))();
            break;
          }
          break;
        case KEY_BACKSPACE:
          if(current->t == TEXTBOX) {
              if(getTextboxCurrentLength(current) >= 0) {
                getTextboxUserInput(current)[current->textbox_current_input_length--] = '\0';
                if(current->textbox_current_input_length < 0) current->textbox_current_input_length = 0;
                current->update(current,2);
              }
          }
          break;
        default:
          txt:
            if(current->t == TEXTBOX) {
              if(getTextboxCurrentLength(current) < getTextboxMaxTextLength(current)) {
                  if(current->textbox_filter(c)) {
                    getTextboxUserInput(current)[current->textbox_current_input_length++] = c;
                    current->update(current,2);
                  }
              }
            }
          break;
      }
    }

    if(c == screen->downKey) {
      iidx = updateInteractable(iidx, 0);
    }else if(c == screen->upKey) {
      iidx = updateInteractable(iidx,1);
    }
    refresh();
  }
}

/*
  *ADD FUNCTIONS
*/
void addItem(sclui_screen *screen, sclui_item *item) {
  assert(screen->items_current_length < screen->items_length);
  screen->items[(screen->items_current_length)++] = item;
  item->screen = (void*)screen;
}

void addInteractableItem(sclui_screen *screen, sclui_interactable_item *item) {
  assert(screen->interactable_items_current_length < screen->interactable_items_length);
  screen->interactable_items[(screen->interactable_items_current_length)++] = item;
  item->screen = (void*)screen;
}

/*
  *CREATE FUNCTIONS
*/

sclui_interactable_item *createInteractableItem(
    char *text,void(*action)(),bool(*filter)(char),type t,
    int x, int y, int max_text_length, int defaultValue, color *c, color *fc, int cp, int cpf
  ) {
  sclui_interactable_item *s = (sclui_interactable_item*)calloc(1,sizeof(sclui_interactable_item));
  assert(s != NULL);
  s->text = text;
  s->t = t;
  s->x = x;
  s->y = y;
  s->enabled = true;
  switch (t) {
    case TEXTBOX:
      s->textbox_max_text_length = max_text_length;
      s->textbox_usrInput = calloc(max_text_length,sizeof(char));
      assert(s->textbox_usrInput != NULL);
      s->textbox_filter = filter == NULL ? &defaultTextBoxFilter : filter;
      s->textbox_current_input_length = 0;
      s->update = &updateTextbox;
      break;
    case CHECKBOX:
      s->checkbox_defaultVal = defaultValue;
      s->update = &updateCheckbox;
      break;
    default:
      s->button_action = action;
      s->update = &updateButton;
      break;
  }
  s->center = &centerInteractableItem;
  s->text_length = getTextLength(text);
  s->bcolor = c;
  s->fcolor = fc;
  s->cp = cp;
  s->cpf = cpf;
  return s;
}

sclui_screen *initScreen(char *title, int interactableItemsCount, int itemsCount, int width, int height, int upKey, int downKey, color *color) {
  assert(color != NULL);
  sclui_screen *s = (sclui_screen*)calloc(1,sizeof(sclui_screen));
  assert(s != NULL);
  s->interactable_items = (sclui_interactable_item**)calloc(interactableItemsCount,sizeof(sclui_interactable_item*));
  assert(s->interactable_items != NULL);
  s->interactable_items_length = interactableItemsCount;
  s->items = (sclui_item**)calloc(itemsCount,sizeof(sclui_item*));
  assert(s->items != NULL);
  s->items_length = itemsCount;
  s->width = width;
  s->height = height;
  s->title = title;
  s->upKey = upKey;
  s->downKey = downKey;
  s->title_length = getTextLength(title);
  s->interactable_items_current_length = 0;
  s->items_current_length = 0;
  s->color = color;
  return s;
}

sclui_item *createItem(char *text, int x, int y) {
  sclui_item *s = (sclui_item*)calloc(1,sizeof(sclui_item));
  assert(s != NULL);
  s->text = text;
  s->text_length = getTextLength(text);
  s->y = y;
  s->center = &centerItem;
  s->x = x;
  return s;
}
