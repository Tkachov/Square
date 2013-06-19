﻿# класс Button

## Общая информация

Класс Button используется для создания кнопок. Он наследует класс [Object](04_Object.md).  
Когда кнопку нажимают, она вызывает функцию, переданную с помощью указателя на класс [functor](06_Using_functors.md).  
Существует четыре состояния кнопки:
* «up», означающее, что курсор не наведён на кнопку;
* «over», означающее, что курсор наведён на кнопку;
* «pressed», означающее, что курсор наведён на кнопку и кнопка мыши была нажата или зажата;
* «disabled», означающее, что кнопка не реагирует на действия пользователя.

Каждому состоянию соответствует отдельный объект класса [Sprite](13_Sprite.md).

Кнопка содержит надпись, представленную объектом класса [Text](14_Text.md), которая отрисовывает текст поверх спрайта состояния кнопки.

## Наследование класса Button

Button является объектом класса Object, т.е. его функции **[update()](04_Object.md#void-updateinput)** и **[draw()](04_Object.md#void-drawsdl_surface)** могут (и должны) быть перегружены. Но сам класса Button содержит защищённые функции, управляющие его поведением:

##### `void redraw()`
Функция, которая вызывается каждый раз, когда кнопку нужно перерисовать (когда состояние, шрифт надписи или ещё что-нибудь изменилось).  
Функция обновляет состояние кнопки.  

----
##### `void update_label()`
Эта функция должна вызываться каждый раз, когда надпись или кнопка изменились, чтобы поместить надпись в нужное место.  
Обычно вызывается из функции **[redraw()](15_Button.md#void-redraw)**.

## Функции  

##### `Button(functor* = 0)`
Конструктор, может принимать объект класса functor, который будет использован при нажатии на кнопку.  

----
##### `virtual void draw(SDL_Surface*)` [наследуется из [Object](04_Object.md#void-drawsdl_surface)]
Отрисовывает себя на экран.  

----
##### `virtual void update(Input*)` [наследуется из [Object](04_Object.md#void-updateinput)]
Обновляет состояние и вызывает функцию, если кнопка мыши была нажата.  

----
##### `void set_up_state(Sprite)`
Устанавливает Sprite, соответствующий состоянию «up».  

----
##### `void set_over_state(Sprite)`
Устанавливает Sprite, соответствующий состоянию «over».  

----
##### `void set_pressed_state(Sprite)`
Устанавливает Sprite, соответствующий состоянию «pressed».  

----
##### `void set_disabled_state(Sprite)`
Устанавливает Sprite, соответствующий состоянию «disabled».  

----
##### `void set_states(Sprite up, Sprite over, Sprite pressed, Sprite disabled)`
Устанавливает объекты Sprite, соответствующие состояниям «up», «over», «pressed» и «disabled».  

----
##### `void set_font(TTF_Font*)`
Устанавливает шрифт надписи.  

----
##### `void set_color(SDL_Color)`
Устанавливает цвет надписи. 

----
##### `void set_text(string)`
Устанавливает текст надписи.  

----
##### `void set_label(TTF_Font* font, SDL_Color color, string text)`
Устанавливает шрифт, цвет и текст надписи.  

----
##### `void set_func(functor*)`
Устанавливает указатель на объект класса functor.  

----
##### `void set_pixel_perfect(bool)`
Устанавливает значение настройки «пиксельной точности».  
Если параметр равен **true**, кнопка будет проверять, находится ли курсор на непрозрачной области спрайта или нет.  
В противном случае кнопка будет проверять только находится ли курсор внутри прямоугольной области кнопки (что проще).  

----
##### `void set_disabled(bool)`
Устанавливает, отключена ли кнопка. (отключена при **true**, включена при **false**)  
Если кнопка отключена, она примет состояние «disabled» и не будет реагировать на действия пользователя.  

----
##### `void set_holding_click_delay(int delay)`
Устанавливает интервал между вызовами функции, если кнопка мыши зажата.  
Если параметр **delay** равен 0, функция будет вызываться лишь в момент, когда кнопка мыши была только что нажата.  
В противном случае функция будет вызываться каждые **delay** кадров пока кнопка мыши зажата.  

----
##### `bool is_disabled()`
Возвращает **true**, если кнопка отключена.  
   
   
**Предыдущий файл:** [класс Text](14_Text.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [класс Window](16_Window.md) 