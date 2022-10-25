Simple Command Line User Interface
===================================

How To: Compile
===============

Example, how to compile the single screen example from samples/

.. code-block:: CPP
    
    g++ singleScreen.cpp -I ../ ../sclui.cpp -lncurses

How To: Create own Item
=======================
If you want an **non interactable** Item, extend on the **BasicItem**-Class.

If you want an **interactable** Item, extend on the **Interactable**-Class.

For both classes you have to impliment some methods. 

The types of the items can be:

.. code-block:: CPP

    enum {BASIC,BUTTON,CHECKBOX,TEXTBOX}

Colors
=====
.. image:: https://camo.githubusercontent.com/c38a8df34b8e14930fbabcd61bbc8cb30b7dcaddab54b99a3b5b065cf8856411/68747470733a2f2f692e696d6775722e636f6d2f436c38337438342e706e67
*Number = Color*

Setup
====
.. code-block:: CPP

    void initSclui();

General
=======

Quit
-----
I made a quit method, so you don't have to. (If you use pointers, you need to free them by yourself. Then you can call the quit method)

.. code-block:: CPP
    
    void doQuit()
  

TextBox Filter
---------------
I already made three common textbox filters.

TextBox Filter Is Text
^^^^^^^^^^^^^^^^^^^^
.. code-block:: CPP

    bool TextBoxFilterIsText(int c)
    
TextBox Filter Is Number
^^^^^^^^^^^^^^^^^^^^^^
.. code-block:: CPP
    
    bool TextBoxFilterIsNumber(int c)
    
TextBox Filter Allow All
^^^^^^^^^^^^^^^^^^^^^^^^
.. code-block:: CPP

    bool TextBoxFilterAllowAll(int c)

Terminal Dimensions
-------------------
Get the current column- and row-count of the terminal

Get Max X
^^^^^^^^^^ 
.. code-block:: CPP

    int getMaxX();

Get Max Y
^^^^^^^^^^
.. code-block:: CPP

    int getMaxY();

Classes
=====

Screen
------

Constructor
^^^^^^

.. code-block:: CPP
    
    Screen(std::string pTitle, int pWidth, int pHeight, char pHFrame, char pVFrame);

Functions
^^^^^^

Add Item
"""""
.. code-block:: CPP
    
    void addItem(BasicItem *i);
    
Add SubScreen
"""""
.. code-block:: CPP

    void addSubScreen(Screen *i);

Center Item
"""""""""""
.. code-block:: CPP

    void centerItem(Screen::axis pAxis, BasicItem *i);

Draw
""""
Draw only needs to be called when the screen is initially *startet*. Changes that happen, after *draw* was called can be applied using *update*

.. code-block:: CPP

     void draw();
Update
""""""
.. code-block:: CPP

    void update();




Text
----

Constructor
^^^^^^^^^^^^
.. code-block:: CPP

    Text(std::string pName,int px, int pY,int pColor);

TextBox
------

Constructor
^^^^^^^^^^^
.. code-block:: CPP
    
    TextBox(std::string pName,int px, int pY, int pMaxLength,int pColor, int pColorFocus, bool(*pFilter)(int), char pSplitter);
    
Functions
^^^^^^^^^
Filter
""""""
Filter is can be set to allow certain characters. If not set, every character will be allowed

.. code-block:: CPP

    bool(*filter)(int) = nullptr;
    
Append
""""""
.. code-block:: CPP

    void append(char c);
Pop
"""
.. code-block:: CPP

    void pop();
    
Default Key Press Event
"""""""""""""""""""""""
It is the default event, that is called when no event is registered. It is public so it can be used in custom press events to avoid code duplication!

.. code-block:: CPP

    void defaultKeyPressEvent(int c);

Events
^^^^^^^

On Key Press
""""""""""""
.. code-block:: CPP

    void(*onKeyPress)(int) = nullptr;

CheckBox
--------
Constructor
^^^^^^^^^^^
.. code-block:: CPP

    CheckBox(std::string pName,int px, int pY,int pColor, int pColorFocus, bool defaultValue);

Functions
^^^^^^^^^^
    
Events
^^^^^^^

On CheckBox Change
""""""""""""""""""
.. code-block:: CPP

    void(*onCheckBoxChange)() 
Button
------

Constructor
^^^^^^^^^^^^ 
.. code-block:: CPP

    Button(std::string pName,int px, int pY,int pColor, int pColorFocus);

Events
^^^^^^
On Button press
""""""""""""""""
.. code-block:: CPP

    void(*onButtonPress)() = nullptr;
