# Simple Command Line User Interface

SCLUI extends ```curses.h``` with prebuild components to create simple but good looking Command Line User Interfaces!

SCLUI should only be used in terminals, that support colors.

---
## This extension is in an very early stage and might contain many bugs!
---

## Docs

### Setup

```C
//Curses init
WINDOW *w = initscr();

//check
assert(w != NULL);

//call setup
setup();

//(optional) setX and Y of window
setConfig(0,0);
```

### Create Window

```C
/*
  *@Params
  *1. The title
  *2. The amount of interactable items
  *3. The amount of itmes
  *4. The width
  *5. The height
  *6./7. The control keys to switch between elements
*/
sclui_screen *screen = initScreen("title",3,1,45,45,KEY_LEFT,KEY_RIGHT);
``` 

### Create Interactable Items
#### Button
#### Textbox
#### Checkbox
### Positioning

### Create Item
