# Functor class

Functors are special objects that store a pointer to the function. To make it work, the class that uses Functor should make **Functor\<ClassNameHere\>** a friend. For example, if My_Class uses Functor, it should make **Functor\<My_Class\>** a friend.

Pointers to these Functors can be passed to any other class. The trick is that other classes are waiting for pointer to functor (first symbol is lower-case in this case). This means other classes should not know anything about the class that passed them the functor they needed.

Simple example:

     //file "Function_Container.h"
     #include "Functor.h"
     #include "Button.h"
    
     class Function_Container
     {
     private:
      friend class Functor<Function_Container>; //make a friend
      void fnc_do_something(); //this function will be called from Button class
      Button* b;
    
     public:
      Function_Container() {
       b = new Button(new Functor<Function_Container>(this, &Function_Container::fnc_do_something));
       //pass a new Functor of this class that points to fnc_do_something function
      }
     };
     
----

     //file "Button.h"
     #include "Functor.h"
    
     class Button
     {
     private:
      functor* func;
    
     public:
      Button(functor* f = 0): func(f) {};
      ~Button() { if(func) delete func; } //don't forget to free memory
    
      void press() {
       if(func) (*func)(); //dereferencing the pointer (and getting functor) and using it's operator()
       //this calls the original function
      }
     }

You can notice how the Button class does not know anything about Function_Container class. That's how you can use Functors in your own projects (they are supported by [Button](17_Button.md), [Fade](18_Fade.md) and [Timer](19_Timer.md) classes).  
   
   
**Previous file:** [Logger class](10_Logger.md)  
**[Contents](00_Contents.md)**  
**Next file:** [Frame class](12_Frame.md)