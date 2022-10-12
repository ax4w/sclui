# Simple Command Line User Interface

SCLUI extends ```curses.h``` with prebuild components to create simple but good looking Command Line User Interfaces!

SCLUI should only be used in terminals, that support colors.

# For an complete example with multiple screens, look at ```test.c```

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

```C
/*
   *@Params
   *1. The text on the button
   *2. The function that the button executes - needs to be type void(*f)();
   *3./4. The X and Y position
*/
sclui_interactable_item *button = createButton("Next", &sndScreen, 5, 10);
```

#### Textbox

```C
/*
   *@Params
   *1. The text for the textbox
   *2. The function that checks if chars are allow. 
   *   - If NULL every alpha-char and space will be allowed
   *   - Custom functions need to be from type: bool(*f)(char);
   *3. Max input length
   *4./5. The X and Y position
*/
sclui_interactable_item *name = createTextBox("Name", NULL, 15, 5, 20);
```

#### Checkbox

```C
/*
  *@Params
  *1. The text of the checkbox
  *2. The default value
  *   - 0 = unchecked
  *   - 1 = checked
  *3./4. The X and Y position
*/
sclui_interactable_item *checkbox1 = createCheckBox("Check",1,5,5);
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

### Positioning

Positioning must be done before calling ```runScreen(screen);``` !

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

## Adding to the Screen

The order, when adding the items, is the same order, when selecting through the items on the screen!

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


