# Simple Command Line User Interface

SCLUI extends ```curses.h``` with prebuild components to create simple but good looking Command Line User Interfaces!

SCLUI should only be used in terminals, that support colors.

# Usage
Since SCLUI is based on ```curses.h``` you'll start of the same way as any other program, that uses ```curses.h```

Example on an very simple application:

(This code will probably not work, for an working example take a look at ```test.c```)

```C
//basic curses window
WINDOW *w = initscr();
if(w == NULL) exit(-1);

//call setup to apply some basic configuration
setup();

//(optional) set the x and y position of all windows
setConfig(0,0); //sets X and Y to 0

//The colors that are used need to be in an specific pair for each item
//You do not need to set the colors, but this will effect the highlighting and overall usage 
init_pair(2,COLOR_BLACK,COLOR_RED); // Index 2 is always for buttons
init_pair(1,COLOR_BLACK,COLOR_WHITE); // Index 1 is always for the window border

//Create a screen
//The first paramter is the title of the screen
//The second paramter is the number of interactable items
//The third paramter is the number of normal items
//The forth paramter is the width of the screen
//The fith paramter is the height of then screen
//The last two paramters are the keys, which are used to go through the items
sclui_screen *screen1 = initScreen("Title",2,1,45,45,KEY_LEFT,KEY_RIGHT);

//Creating an interactable item

//=Button
//The first paramter is the Button text
//The second paramter is the function that should be executed when the button is clicked
//the third element is the X position
//The fourth element is the Y position
sclui_interactable_item *button = createButton("Button",&clickFunc,5,10);

//=Textbox
//The first paramter is the textbox text
//The second paramter is the filter function for the allowed chars in the textbox. 
//NULL will use the default filter function 
//The third paramter is the X position
//The fourht paramter is the Y positioni
sclui_interactable_item *textbox = createTextBox("Textbox",NULL,5,15);

//(optional) centering
centerInteractableItemX(screen1,button); //centers on the X axsis
centerInteractableItemX(screen1,textbox);

//The order, how you add the items will effect the selection behaviour
addInteractableItem(screen1,textbox);
addInteractableItem(screen1,button);

//Show the screen
runScreen(screen1);
```




# This extension is in an very early stage and might contain many bugs!
