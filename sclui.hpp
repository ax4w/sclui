#pragma once
#define COLOR_BLANK -1
#include <vector>
#include <string>
#include <string_view>
#include <any>
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
            enum class types {
                BASIC = 0,
                BUTTON = 1,
                CHECKBOX = 2,
                TEXTBOX = 3
            };
            virtual void draw(bool v) = 0;
            void moveTo();
            void (*onDraw)() = nullptr;
            void (*onDestruct)() = nullptr;
            std::string name = ("");
            int x,y,color, colorFocus;
            bool visible = true;
            BasicItem(std::string name, int x, int y, int color, int colorFocus):
                name{name},x{x},y{y},color{color},colorFocus{colorFocus} {}
        protected:
            bool interactable = false;
            int itemIndex;
            types type;
            void chooseColor(bool b);
    };

    template<class T>
    class Interactable : public BasicItem {
        public:
            bool enabled = true;
            T value;
            Interactable(std::string name, int x, int y, int color, int colorFocus) :
                BasicItem(name,x,y,color,colorFocus)
                {interactable = true;};
    };

    class TextBox : public Interactable<std::string> {
        private:
            virtual void draw(bool v) override;
            char splitter;
            
        public:
            
            bool(*filter)(int) = nullptr;

            void(*onKeyPress)(int) = nullptr;

            void defaultKeyPressEvent(int c);
            int maxLength;
            TextBox(std::string  name,int x, int y,int color, int colorFocus,int maxLength, bool(*filter)(int), char splitter);
            
            
            void append(char c);
            void pop();
    };

    class CheckBox : public Interactable<bool> {
        private:
            virtual void draw(bool v) override;
        public:

            CheckBox(std::string  name,int x, int y,int color, int colorFocus, bool value);

            void(*onCheckBoxChange)() = nullptr;

    };

    class Button : public Interactable<std::any> {   
        private:
            virtual void draw(bool v) override;
            
        public:
            void(*onButtonPress)() = nullptr;
            Button(std::string  pName,int px, int pY,int pColor, int pColorFocus);

        };

    class Text : public BasicItem{
        private:
            virtual void draw(bool v) override;
        public:
            Text(std::string  pName,int px, int pY,int pColor);

            
    };

    class Screen {
        friend class BasicItem;
        friend class CheckBox;
        friend class Interactable<bool>;
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