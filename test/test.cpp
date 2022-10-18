#include "sclui.h"

int main(void) {
    initSclui();
    Screen mainScreen("Test",30,15,'-','|');
    
    Button *button1 = new Button("test",1,1,COLOR_BLUE, COLOR_GREEN, &doQuit);
    Text *text1 = new Text("Hallo welt",1,3,COLOR_BLANK);
    CheckBox *checkbox1 = new CheckBox("check",1,6,COLOR_CYAN, COLOR_RED,false);
    TextBox *textbox1 =  new TextBox("text",1,9,5,COLOR_BLUE, COLOR_GREEN, &isText);
    mainScreen.addItem(button1);
    mainScreen.addItem(text1);
    mainScreen.addItem(checkbox1);
    mainScreen.addItem(textbox1);
    mainScreen.centerItem(mainScreen.X,button1);
    mainScreen.centerItem(mainScreen.X,text1);
    mainScreen.centerItem(mainScreen.X,checkbox1);
    mainScreen.centerItem(mainScreen.X,textbox1);

    //mainScreen.getItemByName("test");
    mainScreen.draw();
    return 0;
}