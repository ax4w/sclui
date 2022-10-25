#pragma once
#define COLOR_BLANK -1
#include <vector>
#include <string>
#include <string_view>
#include <curses.h>
#include <assert.h>

namespace sclui {
    
    void initSclui();

    bool TextBoxFilterIsText(int c);

    bool TextBoxFilterIsNumber(int c);

    bool TextBoxFilterAllowAll(int c);

    void doQuit();

    int getMaxX();
    int getMaxY();
    
    class BasicItem {
        friend class Screen;
        public:
            enum types {BASIC,BUTTON,CHECKBOX,TEXTBOX};
            int itemIndex;
            types getType() const;
            int getX() const;
            int getY() const;
            void setX(int pX);
            void setY(int pY);
            bool isInteractable() const;
            void setInteractable(bool v);
            void moveTo();
            void setColor(int c);
            void setColorFocus(int c);
            bool isVisible() const;
            void setVisible(bool v);
            virtual void draw(bool v) = 0;
            void (*onDraw)() = nullptr;
            void (*onDestruct)() = nullptr;
        protected:
            std::string name = ("");
            int x,y,color, colorFocus;
            bool interactable,visible = true;
            types type;
            void chooseColor(bool b);
    };

    template <class T>
    class Interactable : public BasicItem{
        friend class Screen;
        public:
            virtual T *getValue() = 0;
    };

    class TextBox : public Interactable<std::string> {
        private:
            virtual void draw(bool v) override;
            char splitter;
        public:
            bool(*filter)(int) = nullptr;

            void(*onKeyPress)(int) = nullptr;

            void defaultKeyPressEvent(int c);

            TextBox(std::string_view  pName,int px, int pY, int pMaxLength,int pColor, int pColorFocus, bool(*pFilter)(int), char pSplitter);
            
            virtual std::string *getValue() override;
            int maxLength;
            std::string value;
            void append(char c);
            void pop();
    };

    class CheckBox : public Interactable<bool> {
        private:
            bool value;
            virtual void draw(bool v) override;
        public:
            CheckBox(std::string_view  pName,int px, int pY,int pColor, int pColorFocus, bool defaultValue);

            void(*onCheckBoxChange)() = nullptr;
            virtual bool *getValue() override;
            void setValue(bool v);
    };

    class Button : public Interactable<void> {   
        private:
            virtual void draw(bool v) override;
        public:
            void(*onButtonPress)() = nullptr;

            Button(std::string_view  pName,int px, int pY,int pColor, int pColorFocus);

            
            virtual void *getValue() override;
        };

    class Text : public BasicItem{
        private:
            virtual void draw(bool v) override;
        public:
            Text(std::string_view  pName,int px, int pY,int pColor);

            
    };

    class Screen {
        friend class BasicItem;
        friend class TextBox;
        friend class Button;
        friend class CheckBox;
        private:
            std::string title;
            bool isDragging = false,isFocused = false;
            int vecIndex,subScreenIndex;
            BasicItem *currentItem;
            
            void run();
            void drawFrame(int v);
            void drawItems();
            void destroyHelper(Screen *n);
            void doMove(int mov);
            bool selectNext(BasicItem *i);
            BasicItem *getFirstInteractableItem();
            void handleDrag(int c);
            void switchFocus();
            void moveHelper(int i);
        
        public:

            int x,y,width, height;
            Screen(std::string_view pTitle, int pWidth, int pHeight, int pX, int pY);
            
            void(*onDestruct)() = nullptr;
            void(*onFocus)()= nullptr;
            void(*onUnFocus)()= nullptr;
            void(*onDragBegin)()= nullptr;
            void(*onDrag)()= nullptr;
            void(*onDrop)()= nullptr;

            
            void addItem(BasicItem *i);
            void addSubScreen(Screen *i);
            void setTitle(std::string s);

            BasicItem *getItemByName(const char *name);

            enum axis {X,Y,XY};

            void centerItem(Screen::axis pAxis, BasicItem *i);

            std::vector<BasicItem *> items = {};
            std::vector<Screen *> subScreens = {};

            void draw();
            void update();

            void setBorder(bool v);
            bool border = true;
            Screen *motherScreen = nullptr;
        };

}