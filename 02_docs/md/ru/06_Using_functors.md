# класс Functor

Функторы — это специальные объекты, в которых хранится указатель на функцию. Чтобы заставить их работать, использующий их класс должен сделать **Functor\<ClassNameHere\>** другом. Например, если класс My_Class использует класс Functor, он должен сделать другом **Functor\<My_Class\>**.

Указатели на объект Functor может быть передан любому другому классу. Трюк заключается в том, что другие классы ожидают указатель на functor (в данном случае с маленькой буквы). Это значит, что другим классам не нужно знать, какой именно класс передал функтор, который им был нужен.

Простой пример:

     //file "function_container.h"
     #include "functor.h"
     #include "button.h"
    
     class Function_Container
     {
     private:
      friend class Functor<Function_Container>; //делаем другом
      void fnc_do_something(); //эту функцию мы вызовем из класса Button
      Button* b;
    
     public:
      Function_Container() {
       b = new Button(new Functor<Function_Container>(this, &Function_Container::fnc_do_something));
       //передадим новый Functor этого класса, указывающий на функцию fnc_do_something
      }
     };
     
----

     //file "button.h"
     #include "functor.h"
    
     class Button
     {
     private:
      functor* func;
    
     public:
      Button(functor* f = 0): func(f) {};
      ~Button() { if(func) delete func; } //не забывайте освобождать память
    
      void press() {
       if(func) (*func)(); //разыменовываем указатель (чтобы получить functor) и используем его operator()
       //эта конструкция вызывает оригинальную функцию
      }
     }

Как вы можете заметить, класс Button ничего не знает про класс Function_Container. Вот так вы и можете использовать объекты класса Functor в своих собственных проектах (они поддерживаются классами [Button](15_Button.md) и [Timer](17_Timer.md)). Файл "functor.h" уже включён в файл "screen.h", так что если вы наследуете класс [Screen](03_Screen.md), вам даже не придётся подключать этот файл, чтобы использовать объекты класса Functor в своём классе.  
   
   
**Предыдущий файл:** [класс Game](05_Game.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [класс String_Table](07_String_Table.md)