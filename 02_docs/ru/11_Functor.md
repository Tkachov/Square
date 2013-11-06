# Класс Functor

Функторы — это специальные объекты, хранящие указатель на функцию. Чтобы они могли работать, использующий их класс должен сделать **Functor\<ClassNameHere\>** другом. Например, если класс My_Class использует Functor, он должен сделать **Functor\<My_Class\>** другом.

Pointers to these Functors can be passed to any other class. The trick is that other classes are waiting for pointer to functor (first symbol is lower-case in this case). This means other classes should not know anything about the class that passed them the functor they needed.

Простой пример:

     //файл "Function_Container.h"
     #include "Functor.h"
     #include "Button.h"
    
     class Function_Container
     {
     private:
      friend class Functor<Function_Container>; //сделаем другом
      void fnc_do_something(); //эту функцию мы будем вызывать из класса Button
      Button* b;
    
     public:
      Function_Container() {
       b = new Button(new Functor<Function_Container>(this, &Function_Container::fnc_do_something));
       //передадим новый Functor для этого класса, указывающий на функцию fnc_do_something
      }
     };
     
----

     //файл "Button.h"
     #include "Functor.h"
    
     class Button
     {
     private:
      functor* func;
    
     public:
      Button(functor* f = 0): func(f) {};
      ~Button() { if(func) delete func; } //не забудем очистить память
    
      void press() {
       if(func) (*func)(); //разыменовывание указателя (получение functor) и использование его operator()
       //это вызовет оригинальную функцию
      }
     }

Как вы могли заметить, класс Button ничего не знает о классе Function_Container. Так и используются объекты класса Functor (они поддерживаются классами [Button](17_Button.md), [Fade](18_Fade.md) и [Timer](19_Timer.md)).  
   
   
**Предыдущий файл:** [Класс Logger](10_Logger.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [Класс Frame](12_Frame.md)