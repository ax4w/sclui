# Simple Command Line User Interface for C++

SCLUI extends ```curses.h``` with prebuild components to create simple but good looking Command Line User Interfaces!

SCLUI should only be used in terminals, that support colors.

## Colors
![img](https://i.imgur.com/Cl83t84.png)

*Number = Color*


## Docs

**For some examples, check out the [samples](https://github.com/0x3alex/sclui/tree/main/sample) or [SimplMath](https://github.com/0x3alex/SimplMath)**

**Note for using SubScreens - Currently subscreens can't contain subscreens**

**Examples**

**Screen->SubScreen [OK]**

**Screen->SubScreen->SubScreen [NOT OK]**

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

##### Add SubScreen to Screen
```C++
void addSubScreen(Screen *n)
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
# GetWith
```C++
int getWith() const;
```

# GetHeight
```C++
int getHeight() const;
```

# getX
```C++
int getX() const;
```

# getY
```C++
int getY() const;
```

# setWidth
```C++
void setWith(int v);
```

# setHeight
```C++
void setHeight(int v);
```

# setX
```C++
void setX(int v);
```

# setY
```C++
void setY(int v);
```

# setBorder
```C++
void setBorder(bool v);
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




