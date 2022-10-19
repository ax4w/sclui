#include "sclui.h"

//global scope to access it in extOnV
TextBox *textbox1 = nullptr;

void returnOnV(int c) {
    if(c == 'v') return;
    //will execute normal behaviour if key is not v
    textbox1->defaultKeyPressEvent(c);
    
}

int main(void) {
    initSclui();
    Screen mainScreen("Test",30,15,'-','|');
    
    Button *button1 = new Button("test",1,1,COLOR_BLUE, COLOR_GREEN);
    button1->onButtonPress = &doQuit;
    Text *text1 = new Text("Hallo welt",1,3,COLOR_BLANK);
    CheckBox *checkbox1 = new CheckBox("check",1,6,COLOR_CYAN, COLOR_RED,false);
    checkbox1->onCheckBoxChange = &doQuit;
    textbox1 =  new TextBox("text",1,9,5,COLOR_BLUE, COLOR_GREEN, &TextBoxFilterIsText);
    textbox1->onKeyPress = &returnOnV;
    mainScreen.addItem(button1);
    mainScreen.addItem(text1);
    mainScreen.addItem(checkbox1);
    mainScreen.addItem(textbox1);
    mainScreen.centerItem(mainScreen.X,button1);
    mainScreen.centerItem(mainScreen.X,text1);
    mainScreen.centerItem(mainScreen.X,checkbox1);
    mainScreen.centerItem(mainScreen.X,textbox1);

    mainScreen.draw();
    return 0;
}