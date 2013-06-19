# класс Image

## Общая информация

Класс Image используется движком, чтобы хранить текстуры (и соответствующие пиксели изображения как SDL_Surface). Он наследут класс [Object](04_Object.md), то есть вы можете использовать класс Image для создания статичного изображения на экране (указатель на объект Image возвращается функцией **[Loader::load_texture()](09_Loader.md#image-load_texturestring-filename-bool-keep_surface--true)**). Рекомендуется, правда, использовать для этого класс [Sprite](13_Sprite.md).

## Функции

##### `void draw(SDL_Surface*)` [наследуется из [Object](04_Object.md#void-drawsdl_surface)]
Отрисовывает храняющуюся текстуру.  

----
##### `void draw(int x, int y, SDL_Surface*)` [наследуется из [Object](04_Object.md#virtual-void-drawint-x-int-y-sdl_surface)]
Отрисовывает храняющуюся текстуру со сдвигом по осям X и Y.  

----
##### `void update(Input*)` [наследуется из [Object](04_Object.md#void-updateinput)]
Если курсор находится над текстурой и пересекает её, то функция «съедает» событие перемещения мыши. Если переменная **this.eat_click** равна **true**, «съедает» и событие нажатия мыши.  

----
##### `GLuint* const img()`
Возвращает индекс OpenGL-текстуры.  

----
##### `SDL_Surface* const bmp()`
Возвращает указатель на SDL_Surface, в котором хранятся все пиксели изображения.  

----
##### `bool eating_clicks()`
Возвращает значение переменной **this.eat_click**.  
(См. также **[void update(Input*)](12_Image.md#void-updateinput-inherited-from-object)**.)  

----
##### `int w()`
Возвращает ширину изображения.  

----
##### `int h()`
Возвращает высоту изображения. 

----
##### `int pw()`
Возвращает ширину текстуры (может быть только степенью двойки).  

----
##### `int ph()`
Возвращает высоту текстуры (может быть только степенью двойки).  

----
##### `void set_eating_clicks(bool)`
Устанавливает значение переменной **this.eat_click**.  
(См. также **[void update(Input*)](12_Image.md#void-updateinput-inherited-from-object)**.)  

----
##### `void set_img(GLuint*)`
Устанавливает индекс OpenGL-текстуры, хранящийся в данном объекте. Не освобождает память текстуры с предыдущим индексом.  

----
##### `void set_bmp(SDL_Surface* s)`
Устанавливает указатель на SDL_Surface, хранящийся в данном объекте. Не освобождает память, занятую предыдущим SDL_Surface.  
   
   
**Предыдущий файл:** [класс State](11_State.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [класс Sprite](13_Sprite.md)