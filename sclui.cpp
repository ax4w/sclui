#include "sclui.h"
#include <cstring>
#include <curses.h>


namespace sclui {
    #define TAB_KEY '\t'
    #define CONFIRM_KEY ' '
    static int cIndex = 2;

    //doesnt need to be freed manually, since its not "new"
    static Screen *currentScreen = nullptr;

    void doQuit() {
        currentScreen->destroy(); //free all items
        curs_set(1);
        endwin();
        exit(0);
    }

    void initSclui() {
        WINDOW *w = initscr();
        assert(w != NULL);
        raw();
        noecho();
        start_color();
        keypad(stdscr,TRUE);
        clear();
    }

    bool TextBoxFilterIsText(int c) {
        return isalpha(c) || c == ' ';
    }

    bool TextBoxFilterIsNumber(int c) {
        return isdigit(c);
    }

    bool TextBoxFilterAllowAll(int c) {
        return true;
    }

    BasicItem::types BasicItem::getType() const {
        return type;
    }

    bool BasicItem::isVisible() const {
        return visible;
    }
    void BasicItem::setVisible(bool v) {
        visible = v;
    }

    void BasicItem::setColor(int c) {
        color = c;
    }
    void BasicItem::setColorFocus(int c) {
        colorFocus = c;
    }

    std::string BasicItem::getName() const {
        return name;
    }
    int BasicItem::getX() const {
        return x;
    }
    int BasicItem::getY() const {
        return y;
    }

    void BasicItem::setX(int pX) {
        x = pX;
    }
    void BasicItem::setY(int pY) {
        y = pY;
    }

    bool BasicItem::isInteractable() const {
        return interactable;
    }
    void BasicItem::setInteractable(bool v) {
        interactable = v;
    }
    void BasicItem::moveTo() {
        move(currentScreen->getY() + y,currentScreen->getX() + x);
    }

    void BasicItem::chooseColor(bool b) {
        attroff(COLOR_PAIR(itemIndex));
        if(color == COLOR_BLANK) return;
        init_pair(itemIndex,COLOR_BLACK, b ? colorFocus : color);
        attron(COLOR_PAIR(itemIndex));
    }


    Button::Button(std::string pName, int pX, int pY, int pColor, int pColorFocus) {
        name = pName;
        type = BUTTON;
        color = pColor;
        colorFocus = pColorFocus;
        itemIndex = cIndex++;
        interactable = true;
        x = pX;
        y = pY;
    }

    void Button::draw(bool v) {
        chooseColor(v);
        curs_set(0);
        this->moveTo();
        printw("[ %s ]" , name.c_str()); 
        this->moveTo();
    }

    void Button::getValue() {
        return;
    }

    CheckBox::CheckBox(std::string pName,int pX, int pY,int pColor, int pColorFocus, bool defaultValue) {
        name = pName;
        x = pX;
        y = pY;
        color = pColor;
        colorFocus = pColorFocus;
        value = defaultValue;
        interactable = true;
        type = CHECKBOX;
        itemIndex = cIndex++;
    }

    void CheckBox::draw(bool v) {
        chooseColor(v);
        curs_set(0);
        this->moveTo();
        printw("[ %s (%c) ]", name.c_str(), value == true ? 'X' : ' ');
        this->moveTo();
    }

    bool CheckBox::getValue() {
        return value;
    }

    void CheckBox::setValue(bool v) {
        value = v;
    }

    Text::Text(std::string pName,int pX, int pY,int pColor) {
        name = pName;
        x = pX;
        y = pY;
        color = pColor;
        interactable = false;
        type = BASIC;
        itemIndex = cIndex++;

    }
    void Text::draw(bool v) {
        chooseColor(v);
        curs_set(0);
        this->moveTo();
        printw("%s", name.c_str());
        this->moveTo();
    }

    //screen
    Screen::Screen(std::string pTitle,int pWidth, int pHeight, char pHFrame, char pVFrame, int pX, int pY) {
        width = pWidth;
        height = pHeight;
        hFrame = pHFrame;
        vFrame = pVFrame;
        title = pTitle;
        subScreenIndex = 0;
        x = pX;
        y = pY;
    }


    void Screen::addItem(BasicItem *i) {
        items.push_back(i);
    }

    BasicItem *Screen::getFirstInteractableItem() {
        if(items.size() == 0) return NULL;
        int index = 0;
        for(auto &i: items) {
            if(i->isInteractable() && i->isVisible()) {
                vecIndex = index;
                return i;
            }
            index++;
            
        }
        return NULL;
    }

    BasicItem *Screen::getItemByName(const char *name) {
        //auto generate type
        for(auto &i : items) {
            if(i->getName().compare(name)== 0) {
                return i;
            }
        }
        return nullptr;
    }

    TextBox::TextBox(std::string pName,int pX, int pY, int pMaxLength,int pColor, int pColorFocus, bool(*pFilter)(int), char pSplitter) {
        name = pName;
        x = pX;
        y = pY;
        maxLength = pMaxLength;
        itemIndex = cIndex++;
        interactable = true;
        type = TEXTBOX;
        color = pColor;
        colorFocus = pColorFocus;
        filter = pFilter;
        splitter = pSplitter;
    }

    void TextBox::defaultKeyPressEvent(int c) {
        if(c == KEY_BACKSPACE && this->getValueLength() > 0) {
            this->pop();
        }else{
            if(this->getValueLength() < this->getMaxLength() && (*(this->filter))(c)) {
                this->append(c);
            }
        }
        if(this->onDraw != nullptr) (*(this->onDraw))();
        this->draw(true);
    }

    int TextBox::getValueLength() const {
        return value.length();
    }

    int TextBox::getMaxLength() const {
        return maxLength;
    }

    void TextBox::draw(bool v) {
        chooseColor(v);
        curs_set(1);
        this->moveTo();
        printw("[ %s%c" , name.c_str(),splitter); 
        for(int i = 0; i < maxLength; i++) printw(" ");
        printw("]");
        move(currentScreen->getY()+ y, currentScreen->getX() + x+3 + name.length());
        printw("%s",value.c_str());
    }

    std::string TextBox::getValue() {
        return value;
    }
    void TextBox::append(char c) {
        value.push_back(c);
    }
    void TextBox::pop() {
        value.pop_back();
    }

    void TextBox::setText(std::string s) {
        value = s;
    }

    void Screen::drawFrame() {
        move(getY(),getX());
        init_pair(1,COLOR_BLACK,COLOR_WHITE);
        attron(COLOR_PAIR(1));
        for(int i = 0; i <= width; i++) {
            printw("%c",hFrame);
            if(i == 2) {
                addstr(title.c_str());
                i += title.length();
            }
        }
        move(getY()+height,getX());
        for(int i = 0; i <= width; i++) {
            printw("%c",hFrame);
        }
        for(int i = 0; i <= height; i++) {
            move(getY() + i, getX());
            printw("%c",vFrame);
        }
        for(int i = 0; i <= height; i++) {
            move(getY() + i, getX() + width);
            printw("%c",vFrame);
        }
        attroff(COLOR_PAIR(1));
    }

    bool Screen::selectNext(BasicItem *i) {
        if(!i->isInteractable() || !i->isVisible()) return false;
        if(i->onDraw != nullptr) (*(i->onDraw))();
        i->draw(true);
        return true;
    }

    void Screen::doMove(int mov) {
        if(mov == 0)  { //down
            for(int i = vecIndex+1; i < items.size(); i++) {
                if(selectNext(items.at(i))) {
                    if(currentItem->onDraw != nullptr) (*(currentItem->onDraw))();
                    currentItem->draw(false);
                    vecIndex = i;
                    currentItem = items.at(i);
                    if(currentItem->onDraw != nullptr) (*(currentItem->onDraw))();
                    currentItem->draw(true);
                    return;
                }
            }
        }else{ //up
            for(int i = vecIndex-1; i >= 0; i--) {
                if(selectNext(items.at(i))) {
                    if(currentItem->onDraw != nullptr) (*(currentItem->onDraw))();
                    currentItem->draw(false);
                    vecIndex = i;
                    currentItem = items.at(i);
                    if(currentItem->onDraw != nullptr) (*(currentItem->onDraw))();
                    currentItem->draw(true);
                    return;
                }
            } 
        }
        refresh();
    }

    void Screen::drawItems() {
        for(auto &i : items) {
            if(i->isVisible()) {
                if(i->onDraw != nullptr) (*(i->onDraw))();
                i->draw(false);
            }
                
        }
        vecIndex = 0;
        currentItem = getFirstInteractableItem();
        refresh();
        
    }

    void Screen::run() {
        if(currentItem != NULL) {
            if(currentItem->onDraw != nullptr) (*(currentItem->onDraw))();
            currentItem->draw(true);
        }
        CheckBox *checkBoxCast = nullptr;
        Button *buttonCast = nullptr;
        TextBox *textBoxCast = nullptr;
       
        int c;
        for(;;) {
            c = getch();
            switch(c) {
                case TAB_KEY:
                    if(currentScreen->motherScreen != nullptr) {
                        if(currentScreen->motherScreen->subScreenIndex == currentScreen->motherScreen->subScreens.size()-1) {
                            currentScreen->motherScreen->subScreenIndex = 0;
                        }else{
                            currentScreen->motherScreen->subScreenIndex++;
                            
                        }
                        if(currentScreen->onUnFocus != nullptr) (*(currentScreen->onUnFocus))();
                            currentScreen->motherScreen->update();
                    }
                    break;
                case KEY_UP: //arrow up
                    doMove(1);
                    break;
                case KEY_DOWN: //arrow down
                    doMove(0);
                    break;
                case CONFIRM_KEY:
                    switch(currentItem->getType()) {
                        case BasicItem::CHECKBOX:
                            checkBoxCast = (CheckBox*) currentItem;

                            if(checkBoxCast->onCheckBoxChange == nullptr)
                                checkBoxCast->setValue((bool*)(checkBoxCast->getValue())?false:true);
                            else
                                (*(checkBoxCast->onCheckBoxChange))();

                            break;
                        case BasicItem::BUTTON:
                            buttonCast = (Button*) currentItem;
                            if(buttonCast->onButtonPress != nullptr)
                                (*(buttonCast->onButtonPress))();
                            break;
                        case BasicItem::TEXTBOX:
                            if (c == ' ')
                                goto textBoxHandler;
                            break;
                    }
                    if(currentItem->onDraw != nullptr) (*(currentItem->onDraw))();
                    currentItem->draw(true);
                    break;
                default:
                    textBoxHandler:
                        if(currentItem != NULL) {
                            if(currentItem->getType() == BasicItem::TEXTBOX) {
                                textBoxCast = (TextBox*) currentItem;
                                if(textBoxCast->onKeyPress == nullptr) {
                                    textBoxCast->defaultKeyPressEvent(c);
                                }else{
                                    (*(textBoxCast->onKeyPress))(c);
                                }

                            }
                        }
                        
                    break;
            }
            refresh();
        }
    }

    void Screen::update() {
        this->draw();   
    }

    void Screen::draw() {
        clear();
        if(subScreens.size() > 0) {
            for(auto &n : subScreens) {
                currentScreen = n;
                if(n->border) 
                    n->drawFrame();
                n->drawItems();
            }
            currentScreen = subScreens.at(this->subScreenIndex);
            currentScreen->run();
        }else{
            currentScreen = this;
            if(this->border)
                drawFrame();
            drawItems();
            run();
        }
        if(currentScreen->onFocus != nullptr) (*(currentScreen->onFocus))();
        
        
    }

    void Screen::centerItem(Screen::axis pAxis, BasicItem *i) {
        TextBox *textBoxCast = nullptr;
        switch(pAxis) {
            case X:
                switch(i->getType()) {
                    case BasicItem::TEXTBOX:
                        textBoxCast = (TextBox*) i;
                        i->setX((width / 2) - ((i->getName().length() /2) + ((textBoxCast->getMaxLength() + 4) / 2)));
                        break;
                    case BasicItem::CHECKBOX:
                        i->setX((width / 2) - ((i->getName().length() /2) + 4));
                        break;
                    case BasicItem::BUTTON:
                        i->setX((width / 2) - ((i->getName().length() /2) + 2));
                        break;
                    default:
                        i->setX((width / 2) - (i->getName().length() /2));
                        break;
                }
            
                break;
            case Y:
                i->setY(height / 2);
                break;
            default:
                centerItem(X,i);
                centerItem(Y,i);
                break;
        }
    }

    BasicItem *Screen::getItemAt(int index) {
        return items.at(index);
    }

    Screen *Screen::getSubScreenAt(int index) {
        return subScreens.at(index);
    }
    void Screen::addSubScreen(Screen *i) {
        i->motherScreen = this;
        subScreens.push_back(i);
    }

    void Screen::destroyHelper(Screen *n) {
        if(n->items.size() > 0) {
            for(auto &i : n->items) {
                if(i->onDestruct != nullptr)
                    (*(i->onDestruct))();
                delete i;
            }
        }
        if(n->subScreens.size() > 0) {
            for(auto &i : n->subScreens) {
                if(i->onDestruct != nullptr)
                    (*(i->onDestruct))();
                delete i;
            }
        }
    }
    void Screen::destroy() {
        if(this->motherScreen != nullptr) {
            for(auto &n : this->motherScreen->subScreens) {
                destroyHelper(n);
            }
        }else{
            destroyHelper(this);
        } 
    }

    void Screen::setTitle(std::string s) {
        title = s;
    }

    int Screen::getWith() const {
        return width;
    }
    int Screen::getHeight() const {
        return height;
    }
    int Screen::getX() const {
        return x;
    }
    int Screen::getY() const {
        return y;
    }

    void Screen::setWith(int v) {
        width = v;
    }
    void Screen::setHeight(int v) {
        height = v;
    }
    void Screen::setX(int v) {
        x = v;
    }
    void Screen::setY(int v) {
        y = v;
    }

    void Screen::setBorder(bool v) {
        border = v;
    }
}