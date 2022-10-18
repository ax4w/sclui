# Simple Command Line User Interface for C++

SCLUI extends ```curses.h``` with prebuild components to create simple but good looking Command Line User Interfaces!

SCLUI should only be used in terminals, that support colors.

## Docs

### Setup
Simply call:
```C++
initSclui();
```

### Create Screen

Signature is:
```C++
Screen(std::string pTitle, int pWidth, int pHeight, char pHFrame, char pVFrame);
```

Usage is:
```C++
Screen *menu = new Screen("Menu",40,14,'-','|');
```

### Create Items

#### Button
Signature is:
```C++
Button(std::string pName,int px, int pY,int pColor, int pColorFocus, void(*actionEvent)());
```

Usage is:
```C++
Button *quit = new Button("Quit",1,13,COLOR_WHITE,COLOR_RED,&doQuit);
```

#### TextBox
Signaure is:
```C++
TextBox(std::string pName,int px, int pY, int pMaxLength,int pColor, int pColorFocus, bool(*pFilter)(int));
```

Usage is:
```C++
minimum = new TextBox("Text",1,3,4,COLOR_WHITE,COLOR_BLUE,&isText);
```

#### CheckBox
Signature is:
```C++
CheckBox(std::string pName,int px, int pY,int pColor, int pColorFocus, bool defaultValue);
```

Usage is:
```C++
CheckBox *checkbox1 = new CheckBox("check",1,6,COLOR_CYAN, COLOR_RED,false);
```

#### Text

Signature is:
```C++
Text(std::string pName,int px, int pY,int pColor);
```

Usage is:
```C++
Text *text1 = new Text("Hello World",1,3,COLOR_BLANK);
```
### Add Items to Screen

*Function of class Screen*

Signature is:
```C++
void addItem(BasicItem *i)
```

Usage is:
```C++
//menu is a screen
menu->addItem(quit);
```

### Position Items on Screen
#### Center
*Function of class Screen* 

Signature is:
```C++
void centerItem(Screen::axis pAxis, BasicItem *i)
```

Usage is:
```C++
//menu is a screen
menu->centerItem(menu->X,quit);
```

#### Manual
*Functions of class BasicItem*

##### getX

```C++
int getX();
```

##### getY
```C++
int getY();
```

##### setX
```C++
int setX(int pX);
```

##### setY
```C++
int setY(int pY);
```

