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

    enum class axis {
        X,
        Y,
        XY
    };
    
    class BasicItem {
        friend class Screen;
        public:
            enum class types {
                BASIC,
                BUTTON,
                CHECKBOX,
                TEXTBOX
            };
            virtual void draw(bool v) = 0;
            void moveTo(int yOffet, int xOffset);
            void (*onDraw)() = nullptr;
            void (*onDestruct)() = nullptr;
            std::string name = ("");
            int x,y,color, colorFocus;
            bool visible = true;
            BasicItem(std::string_view name, int x, int y, int color, int colorFocus):
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
            Interactable(std::string_view name, int x, int y, int color, int colorFocus, T value) :
                BasicItem(name,x,y,color,colorFocus),
                value{value}
                {interactable = true;};
    };

    class TextBox : public Interactable<std::string> {
        private:
            virtual void draw(bool v) override;
            char splitter;

        public:
            TextBox(std::string_view  name,int x, int y,int color, int colorFocus,int maxLength, bool(*filter)(int), char splitter);
            bool(*filter)(int) = nullptr;
            void(*onKeyPress)(int) = nullptr;
            void defaultKeyPressEvent(int c);
            int maxLength;
            void append(char c);
            void pop();
    };

    class CheckBox : public Interactable<bool> {
        private:
            virtual void draw(bool v) override;

        public:
            CheckBox(std::string_view  name,int x, int y,int color, int colorFocus, bool value);
            void(*onCheckBoxChange)() = nullptr;
    };

    class Button : public Interactable<std::any> {   
        private:
            virtual void draw(bool v) override;
            
        public:
            Button(std::string_view  name,int x, int y,int color, int colorFocus);
            void(*onButtonPress)() = nullptr;
        };

    class Text : public BasicItem{
        private:
            virtual void draw(bool v) override;
        public:
            Text(std::string_view  name,int x, int y,int color);
    };

    class Screen {
        friend class BasicItem;
        friend class CheckBox;

        private:
            
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
            Screen(std::string_view title, int width, int height, int x, int y);

            std::string title;
            int x,y,width, height;
            void(*onDestruct)() = nullptr;
            void(*onFocus)()= nullptr;
            void(*onUnFocus)()= nullptr;
            void(*onDragBegin)()= nullptr;
            void(*onDrag)()= nullptr;
            void(*onDrop)()= nullptr;
            void addItem(BasicItem *i);
            void addSubScreen(Screen *i);
            BasicItem *getItemByName(const char *name);

            

            void centerItem(axis pAxis, BasicItem *i);

            std::vector<BasicItem *> items = {};
            std::vector<Screen *> subScreens = {};

            void draw();
            void update();

            void setBorder(bool v);
            bool border = true;
            Screen *motherScreen = nullptr;
        };

}