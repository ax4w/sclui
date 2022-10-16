# Simple Command Line User Interface for C

SCLUI extends ```curses.h``` with prebuild components to create simple but good looking Command Line User Interfaces!

SCLUI should only be used in terminals, that support colors.

**For an example app look at ![SimplMath](https://github.com/0x3alex/SimplMath)**

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
**Hint: If you want no colors for a sertain object, set the wanted color field to NULL**

### Create Window

```C
/*
  Create Color
  This will be the border color of the screen
*/

color sColor = {
  .b = COLOR_WHITE,
  .f = COLOR_BLACK
};
/*
  *@Params
  *1. The title
  *2. The amount of interactable items
  *3. The amount of itmes
  *4. The width
  *5. The height
  *6./7. The control keys to switch between elements
  *8. - Color
*/
sclui_screen *screen = initScreen("title",3,1,45,45,KEY_LEFT,KEY_RIGHT,sColor);
``` 

### Create Interactable Items

#### Button

```C
/*
  Create the colors
  *.b - background
  *.f - foreground
*/

//normal color
color bColor = {
  .b = COLOR_BLUE,
  .f = COLOR_YELLOW
};

//focus color
color bfColor = {
  .b = COLOR_RED,
  .f = COLOR_YELLOW
};
/*
   *@Params
   *1. The text on the button
   *2. The function that the button executes - needs to be type void(*f)();
   *3./4. The X and Y position
   *5. Color
   *6. Focus Color
*/
sclui_interactable_item *button = createButton("Next", &sndScreen, 5, 10,bColor,bfColor);
```

#### Textbox

```C

/*
  Create the colors
*/

//normal color
color tColor = {
  .b = COLOR_BLUE,
  .f = COLOR_YELLOW
};

//focus color
color tfColor = {
  .b = COLOR_RED,
  .f = COLOR_YELLOW
};
/*
   *@Params
   *1. The text for the textbox
   *2. The function that checks if chars are allow. 
   *   - If NULL every alpha-char and space will be allowed
   *   - Custom functions need to be from type: bool(*f)(char);
   *3. Max input length
   *4./5. The X and Y position
   *6. Color
   *7. Focus Color
*/
sclui_interactable_item *name = createTextBox("Name", NULL, 15, 5, 20,tColor,tfcolor);
```

#### Checkbox

```C

/*
  Create the colors
*/

//normal color
color cColor = {
  .b = COLOR_BLUE,
  .f = COLOR_YELLOW
};

//focus color
color cfColor = {
  .b = COLOR_RED,
  .f = COLOR_YELLOW
};
/*
  *@Params
  *1. The text of the checkbox
  *2. The default value
  *   - 0 = unchecked
  *   - 1 = checked
  *3./4. The X and Y position
  *5. Color
  *6. Focus Color
*/
sclui_interactable_item *checkbox1 = createCheckBox("Check",1,5,5,cColor,cfColor);
```

## Create Items
```C
/*
  *@Params
  *1. The text that shall be displayed
  *2./3. The X and Y position
*/
sclui_item *example_text = createItem("This is a small demonstration application!", 1, 1);
```


## Adding to the Screen

The order, in which the items are added, is the same order, when selecting through the items on the screen!

### Interactable Items
```C
/*
  *@Params
  *1. The screen to add to
  *2. The interactable item that shall be added
*/
addInteractableItem(screen, checkbox1);
```

### Items
```C
/*
  *@Params
  *1. The screen to add to
  *2. The item that shall be added
*/
addItem(screen, example_text);
```

### Positioning

Positioning must be done before calling ```runScreen(screen);``` and after adding the item to the screen

#### Interactable Items

##### Center

```C
/*
  *@Param
  *1. The screen
  *2. The interactable item to center
*/
centerInteractableItemX(screen,checkbox1); //centers on the X axsis
centerInteractableItemY(screen,checkbox1); //centers on the y axsis
```
##### Manual

```C
/*
  *@Params
  *1. The item to position
  *2. The new position
*/
setInteractableItemX(checkbox1, 1);
setInteractableItemY(checkbox1, 1);

/*
  *@Params
  *1. The item to get the position from
*/
int x = getInteractableItemX(checkbox1);
int y = getInteractableItemY(checkbox1);

```

#### Items

##### Center
```C
/*
  *@Params
  *1. The screen
  *2. The item
*/
centerItemX(screen, example_text); //centers on x
centerItemY(screen, example_text); //centers on y
```

#### Manual

```C
/*
  *@Params
  *1. The item to position
  *2. The new position
*/
void setItemX(example_text, 1);
void setItemY(example_text, 1);

/*
  *@Params 
  *1. The item to get the position from
*/
int getItemX(example_text);
int getItemY(example_text);

```
### TIPS

#### If you want to pass values from screen to screen, create the needed elements in an global context

#### To access the items from a screen before running a new screen, use ```currentScreen``` as instance to get an item

#### To get an interactable item, use ```getInteractableItemByText```

