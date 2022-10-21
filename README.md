# Simple Command Line User Interface for C++

SCLUI extends ```curses.h``` with prebuild components to create simple but good looking Command Line User Interfaces!

SCLUI should only be used in terminals, that support colors.

## Colors
![img](https://i.imgur.com/Cl83t84.png)

To get the color you want, enter the the corresponding number


## Docs

### Setup
Simply call:
```C++
initSclui();
```

### Class : Screen

#### Create

```C++
Screen(std::string pTitle, int pWidth, int pHeight, char pHFrame, char pVFrame);
```

#### General
##### Add Items to Screen

```C++
void addItem(BasicItem *i)
```

##### Center Item

```C++
void centerItem(Screen::axis pAxis, BasicItem *i)
```
##### getItemAt
```C++
BasicItem *getItemAt(int index);
```

##### draw
```C++
void draw();
```

##### update
```C++
void update();
```

### Class : BasicItem
#### Text
##### Create

```C++
Text(std::string pName,int px, int pY,int pColor);
```
#### Events

##### onDraw
```C++
void (*onDraw)();
```

##### onDestruct
```C++
void (*onDestruct)();
```

#### General

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
#### isInteractable
```C++
bool isInteractable();
```

#### setInteractable
```C++
void setInteractable(bool v);
```

#### moveTo
```C++
void moveTo();
```

#### setColor
```C++
void setColor(int c);
```

#### setColorFocus
```C++
void setColorFocus(int c);
```

#### isVisible
```C++
bool isVisible();
```

#### setVisible
```C++
void setVisible(bool v);
```

#### draw
```C++
void draw(bool v);
```

### Class : Interactable
Every interactable is an instance of *BasicItem*
#### Button
##### Create

```C++
Button(std::string pName,int px, int pY,int pColor, int pColorFocus);
```
##### Events
###### onDraw
```C++
void(*onButtonPress)();
```

#### TextBox
##### Create

```C++
TextBox(std::string pName,int px, int pY, int pMaxLength,int pColor, int pColorFocus, bool(*pFilter)(int));
```
##### Events

###### onKeyPress
```C++
void(*onKeyPress)(int)
```

##### General

###### setText
```C++
void setText(std::string s);
```

###### getValueLength
```C++
int getValueLength();
```

###### maxLength
```C++
int getMaxLength();
```

###### append
```C++
void append(char c);
```

###### pop
```C++
void pop();
```

#### CheckBox
##### Create

```C++
CheckBox(std::string pName,int px, int pY,int pColor, int pColorFocus, bool defaultValue);
```
#### Events
##### onCheckBoxChange
```C++
void(*onCheckBoxChange)();
```

#### General

##### getValue
```C++
T getValue()
```

##### setValue
```C++
void setValue(bool v);
```




