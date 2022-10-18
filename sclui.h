#pragma once
#define COLOR_BLANK -1
#include <vector>
#include <string>
#include <curses.h>
#include <assert.h>

void initSclui();

bool isText(int c);

bool isNumber(int c);

void doQuit();

class BasicItem {
public:
    typedef enum {BASIC,BUTTON,CHECKBOX,TEXTBOX} types; 
    int itemIndex;
    types getType();
    std::string getName();
    int getX();
    int getY();
    void setX(int pX);
    void setY(int pY);
    bool isInteractable();
    void setInteractable(bool v);
    void moveTo();
    void chooseColor(bool b);
    void setColor(int c);
    void setColorFocus(int c);
    virtual void draw(bool v) = 0;
protected:
    std::string name = ("");
    int x,y,color, colorFocus;
    bool interactable;
    types type;
};

//"Bridge" between BasicItem and all the actual items for the getValue() return type
template <class T>
class Item : public BasicItem{
public:
    virtual T getValue() = 0;
};

class TextBox : public Item<std::string> {
private:
    std::string value;
    int maxLength;
public:
    bool(*filter)(int) = nullptr;
    TextBox(std::string pName,int px, int pY, int pMaxLength,int pColor, int pColorFocus, bool(*pFilter)(int));

    virtual void draw(bool v) override;
    virtual std::string getValue() override;
    int getValueLength();
    int getMaxLength();
    void append(char c);
    void pop();
};

class CheckBox : public Item<bool> {
private:
    bool value;
public:
    CheckBox(std::string pName,int px, int pY,int pColor, int pColorFocus, bool defaultValue);

    virtual void draw(bool v) override;
    virtual bool getValue() override;
    void setValue(bool v);
};

class Button : public Item<void> {
private:
    
public:
    void(*actionEvent)() = nullptr;

    Button(std::string pName,int px, int pY,int pColor, int pColorFocus, void(*actionEvent)());

    virtual void draw(bool v) override;
    virtual void getValue() override;

    void* getActionEvent();
};

class Text : public BasicItem{
public:
    Text(std::string pName,int px, int pY,int pColor);

    virtual void draw(bool v) override;
};

class Screen {
    std::string title;
    int width, height,vecIndex;
    BasicItem* currentItem;
    std::vector<BasicItem *> items = {};
    char hFrame, vFrame;
    void drawFrame();
    void drawItems();
    void run();
    void doMove(int mov);
    bool selectNext(BasicItem *i);
    BasicItem *getFirstInteractableItem();

public:
    Screen(std::string pTitle, int pWidth, int pHeight, char pHFrame, char pVFrame);
    void addItem(BasicItem *i);

    BasicItem *getItemByName(const char *name);

    enum axis {X,Y,XY};

    void centerItem(Screen::axis pAxis, BasicItem *i);

    BasicItem *getItemAt(int index);

    void draw();
    void update();
};
