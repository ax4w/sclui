#include "sclui.hpp"

using namespace sclui;
//global scope to access it in extOnV
static TextBox textbox1 = TextBox("text",1,9,5,COLOR_BLUE, COLOR_GREEN, &TextBoxFilterIsNumber,'|');
static Screen mainScreen = Screen("Test",30,15,0,0); //no pointer

void returnOnV(int c) {
    if(c == 'v') return;
    //will execute normal behaviour if key is not v
    textbox1.defaultKeyPressEvent(c);
    
}

void test() {
    mainScreen.setTitle("world!");
    mainScreen.x = 5;
    mainScreen.y = 5;
    mainScreen.width = 35;
    mainScreen.height = 25;
    mainScreen.update();
}

int main(void) {
    initSclui();
    
    
    //pointer, because items from Screen is type BasicItem*
    Button button1 = Button("test",1,1,11, COLOR_GREEN);

    //doQuit will free every item on that screen
    //every screen will be freed when a new screen is loaded
    button1.onButtonPress = &test; //register press event(
    Text text1 = Text("Hallo\nwelt",1,3,COLOR_BLANK);
    CheckBox checkbox1 = CheckBox("check",1,6,COLOR_CYAN, COLOR_RED,false);
    checkbox1.onCheckBoxChange = &doQuit; //register checkbox change event


    textbox1.onKeyPress = &returnOnV; //register key press event 
    
    //add items
    mainScreen.addItem(&button1);
    mainScreen.addItem(&text1);
    mainScreen.addItem(&checkbox1);
    mainScreen.addItem(&textbox1);

    //center n x
    mainScreen.centerItem(mainScreen.X,&button1);
    mainScreen.centerItem(mainScreen.X,&text1);
    mainScreen.centerItem(mainScreen.X,&checkbox1);
    mainScreen.centerItem(mainScreen.X,&textbox1);

    mainScreen.draw();
    
    return 0;
}