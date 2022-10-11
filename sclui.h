#ifndef SCLUI
#define SCLUI

#include <curses.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

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

typedef struct {
  char* text;
  int x;
  int y;
  void(*action)();
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
sclui_interactable_item *createInteractableItem(char *text, void(*action)(), int x, int y);
sclui_item* createItem(char *text, int x, int y);
void addInteractableItem(sclui_screen *screen, sclui_interactable_item *item); 
void addItem(sclui_screen *screen, sclui_item *item);

#endif
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

sclui_interactable_item *createInteractableItem(char *text, void(*action)(), int x, int y) {
  assert(action != NULL); 
  sclui_interactable_item *s = (sclui_interactable_item*)calloc(1,sizeof(sclui_interactable_item));
  s->text = text;
  s->x = x;
  s->y = y;
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

int updateInteractable(sclui_screen *screen, int iidx, int mov) {
  switch(mov) {
    case 0: //down
      if(iidx < screen->interactable_items_current_length-1) {
        attroff(COLOR_PAIR(2)); //clear color
        addstr(screen->interactable_items[iidx]->text); //reprint current item to remove highlight
        iidx++;
        move(gConfig.posY + screen->interactable_items[iidx]->y, 
            gConfig.posX + screen->interactable_items[iidx]->x);
        attron(COLOR_PAIR(2));
        printw("%s",screen->interactable_items[iidx]->text);
        move(gConfig.posY + screen->interactable_items[iidx]->y, 
            gConfig.posX + screen->interactable_items[iidx]->x);
      }
      break;
    case 1: //up
      if(iidx > 0) {
        attroff(COLOR_PAIR(2)); //clear color
        addstr(screen->interactable_items[iidx]->text); //reprint current item to remove highlight
        iidx--;
        move(gConfig.posY + screen->interactable_items[iidx]->y, 
            gConfig.posX + screen->interactable_items[iidx]->x );
        attron(COLOR_PAIR(2));
        printw("%s",screen->interactable_items[iidx]->text);
        move(gConfig.posY + screen->interactable_items[iidx]->y, 
            gConfig.posX + screen->interactable_items[iidx]->x);
      }
      break;
  }
  attroff(COLOR_PAIR(2));
  refresh(); 
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
  curs_set(0);
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
      move(gConfig.posY + screen->interactable_items[i]->y,gConfig.posX + screen->interactable_items[i]->x);  
      addstr(screen->interactable_items[i]->text);
    }

    //select first interactable item
    move(gConfig.posY + screen->interactable_items[iidx]->y, gConfig.posX + screen->interactable_items[iidx]->x);
    attron(COLOR_PAIR(2));
    addstr(screen->interactable_items[iidx]->text);
    move(gConfig.posY + screen->interactable_items[iidx]->y, gConfig.posX + screen->interactable_items[iidx]->x);
  }
  refresh();
 
  while(1) {
    c  = getch();
    
    if(c == CONFIRM_KEY) {
      (*screen->interactable_items[iidx]->action)();
    }
    
    if(c == screen->downKey) {
      iidx = updateInteractable(screen, iidx, 0);
    }else if(c == screen->upKey) {
      iidx = updateInteractable(screen,iidx,1);
    }
    
  }
}
#endif
