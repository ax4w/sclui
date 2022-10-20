#include "sclui.h"

using namespace sclui;
//global scope to access it in extOnV
static TextBox *textbox1 = nullptr; //public to pass into the event function

void returnOnV(int c) {
    if(c == 'v') return;
    //will execute normal behaviour if key is not v
    textbox1->defaultKeyPressEvent(c);
    
}

int main(void) {
    initSclui();
    Screen mainScreen("Test",30,15,'-','|'); //no pointer
    
    //pointer, because items from Screen is type BasicItem*
    Button *button1 = new Button("test",1,1,11, COLOR_GREEN);

    //doQuit will free every item on that screen
    //every screen will be freed when a new screen is loaded
    button1->onButtonPress = &doQuit; //register press event(
    Text *text1 = new Text("Hallo welt",1,3,COLOR_BLANK);
    CheckBox *checkbox1 = new CheckBox("check",1,6,COLOR_CYAN, COLOR_RED,false);
    checkbox1->onCheckBoxChange = &doQuit; //register checkbox change event
    textbox1 =  new TextBox("text",1,9,5,COLOR_BLUE, COLOR_GREEN, &TextBoxFilterIsNumber);


    textbox1->onKeyPress = &returnOnV; //register key press event 
    
    //add items
    mainScreen.addItem(button1);
    mainScreen.addItem(text1);
    mainScreen.addItem(checkbox1);
    mainScreen.addItem(textbox1);

    //center n x
    mainScreen.centerItem(mainScreen.X,button1);
    mainScreen.centerItem(mainScreen.X,text1);
    mainScreen.centerItem(mainScreen.X,checkbox1);
    mainScreen.centerItem(mainScreen.X,textbox1);

    mainScreen.draw();
    return 0;
}