===================================
Simple Command Line User Interface
===================================

General
========

Init
-----
This needs to be called before any other thing is done!

..  code-block:: cpp

    void initSclui();

TextBox Filters
---------------

Those are some pre-made filters for the textbox component

TextBox Filter Is Text
~~~~~~~~~~~~~~~~~~~~~~~

..  code-block:: cpp

    bool TextBoxFilterIsText(int c);


TextBox Filter Is Number
~~~~~~~~~~~~~~~~~~~~~~~~~

..  code-block:: cpp

    bool TextBoxFilterIsNumber(int c);


TextBox Filter Allow All
~~~~~~~~~~~~~~~~~~~~~~~~~

..  code-block:: cpp

    bool TextBoxFilterAllowAll(int c);


Do Quit
~~~~~~~~

Gracefully quit the programm

..  code-block:: cpp

    void doQuit();


get Max X
~~~~~~~~~~~~~~~~

Returns the number of columns of the current console window

..  code-block:: cpp

    int getMaxX();



get Max Y
~~~~~~~~~~~~~~~~

Returns the number of rows of the current console window

..  code-block:: cpp

    int getMaxY();

Items
=======

Public Fields
---------------
..  code-block:: cpp

    void (*onDraw)(); //event, when drawn
    void (*onDestruct)(); //event, when destroyed
    std::string name = (""); //name of the elemt
    int x,y,color, colorFocus; //x- and y-position, color and focus color
    bool visible = true; //visibility

Interactable Items
-------------------

Public Fields
~~~~~~~~~~~~~~
..  code-block:: cpp

    bool enabled = true; //if the item should be interactable
    T value; // T being the value type of the item, stores the value
    

Button
~~~~~~~

Constructor
""""""""""""""

..  code-block:: cpp

    Button(std::string_view  name,int x, int y,int color, int colorFocus);
    

On Button Press
"""""""""""""""""
onButtonPress is an event, which is fired, when the button is pressed. 
-> Can be NULL.

..  code-block:: cpp

    void(*onButtonPress)();


TextBox
~~~~~~~

Constructor
""""""""""""""

CheckBox
~~~~~~~~

Constructor
""""""""""""""

..  code-block:: cpp

    TextBox(std::string_view  name,int x, int y,int color, int colorFocus,int maxLength, bool(*filter)(int), char splitter);
    

On Check Change
""""""""""""""""
onCheckChange is an event, which is fired, when the value of the checkbox is changed.
-> Can be NULL.


..  code-block:: cpp

    void(*onCheckBoxChange)();

Not Interactable Items
----------------------

Text
~~~~~

Constructor
""""""""""""""

..  code-block:: cpp

    Text(std::string_view  name,int x, int y,int color);


Screen
=======
