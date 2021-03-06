# Класс Main_Window

## Общая информация

Поскольку Square разработан для создания однооконных приложений вроде игр, в нём нет классов для окон, кроме класса для главного окна приложения — Main_Window.

Почти все функции этого класса статичны, то есть вы можете вызывать их откуда вам захочется.

## Функции  

##### `static void create(...)`
    static void create(
     const char* title,
     int x, int y, int w, int h,
     string fullscreen,
     int flags = 0
    )
Эта функция создаёт окно приложения с указанными параметрами. Она автоматически вызывается при запуске или перезапуске приложения. Реальные значения, передаваемые в неё, могут отличаться — туда передаются значения из конфигурационного файла (или значения по умолчанию из файла [settings.h](22_settings_h.md), если в файле их не было).  
Если хотите использовать функцию вручную, передайте заголовок окна как **title**, координаты как **x**, **y** и размеры как **w** и **h**. Если хотите запустить приложение в [полноэкранном режиме](06_Main_Window.md#%D0%9F%D0%BE%D0%BB%D0%BD%D0%BE%D1%8D%D0%BA%D1%80%D0%B0%D0%BD%D0%BD%D1%8B%D0%B5-%D1%80%D0%B5%D0%B6%D0%B8%D0%BC%D1%8B-square), передайте "1", чтобы запустить его в режиме fs_FULLSCREEN_STRETCHED, "2" — для режима fs_FULLSCREEN_WHOLE_SCREEN, "3" — для fs_WINDOWED_STRETCHED или "4" для fs_WINDOWED_WHOLE_SCREEN. Можете также передать какие-нибудь [флаги для окна SDL](http://wiki.libsdl.org/SDL_CreateWindow#Remarks), если хотите.

----
##### `static void destroy()`
Уничтожает окно.  
При этом удаляется контекст OpenGL, так что все загруженные текстуры будут выгружены из памяти, поскольку их индексы будут утеряны.
Эта функция вызывается автоматически, когда приложение закрывается или перезапускается.  

----
##### `static void swap()`
Обновляет окно.  
Автоматически вызывается после отрисовки каждого кадра.

----
##### `static void update_window_size()`
Обновляет информацию о размерах окна.  
Нужно вызывать в случае, если что-то могло изменить размер окна (например, игрок).  
Функция вызывается автоматически, если вы переключаетесь обратно на приложение в системе Android.  

----
##### `static Fullscreen_Mode get_fullscreen()`
Возвращает текущий полноэкранный режим.  

----
##### `static int get_viewport_width(bool refresh = false)`
Возвращает текущую ширину области отрисовки.
Если значение **refresh** равно **true**, также проверяет, изменился ли размер окна и возвращает обновлённое значение.  
Не меняет размеры проекции.  
 
----
##### `static int get_viewport_height(bool refresh = false)`
Возвращает текущую высоту области отрисовки.
Если значение **refresh** равно **true**, также проверяет, изменился ли размер окна и возвращает обновлённое значение.  
Не меняет размеры проекции.  

----
##### `static int get_projection_width()`
Возвращает текущую ширину проекции.
Не изменяет размеры проекции.  
 
----
##### `static int get_projection_height()`
Возвращает текущую высоту проекции.
Не изменяет размеры проекции. 

----
##### `static void set_fullscreen(Fullscreen_Mode fullscreen)`
Устанавливает новый полноэкранный режим, запрашивая проекцию того же размера, что был до вызова функции.  
Может изменить размеры как проекции, так и области отрисовки.  

----
##### `static void set_fullscreen(Fullscreen_Mode fullscreen, int pr_width, int pr_height)`
Устанавливает новый полноэкранный режим, запрашивая проекцию указанного размера.  
Может изменить размеры как проекции, так и области отрисовки.   
 
----
##### `static void set_title(string title)`
Устанавливает новый заголовок окна.  

## Полноэкранные режимы Square

SDL предоставляет три полноэкранных режима:
* **0**, — оконный режим,
* **SDL_WINDOW_FULLSCREEN**, — «поддельный» полноэкранный режим,
* **SDL_WINDOW_FULLSCREEN_DESKTOP**, — «настоящий» полноэкранный режим.

В «поддельном» режиме SDL меняет разрешение экрана так, чтобы соответствовать размеру окна приложения (то есть растягивает его на весь экран).

В «настоящем» режиме вам передаётся весь экран, чтобы вы могли использовать больше пространства.

### Fullscreen_Mode

В Square есть собственное перечисление для полноэкранных режимов из-за проблем с полноэкранными режимами в SDL на Ubuntu.

Оно содержит следующие значения:
* **fs_WINDOWED**, — оконный режим,
* **fs_FULLSCREEN_STRETCHED**, — «поддельный» полноэкранный режим SDL (**SDL_WINDOW_FULLSCREEN**),
* **fs_FULLSCREEN_WHOLE_SCREEN**, — «настоящий» полноэкранный режим SDL (**SDL_WINDOW_FULLSCREEN_DESKTOP**),
* **fs_WINDOWED_STRETCHED**, — эмуляция «поддельного» полноэкранного режима,
* **fs_WINDOWED_WHOLE_SCREEN**, — эмуляция «настоящего» полноэкранного режима.

Первые три просто используют соответствующие режимы SDL, а вот последние два сделаны специально для случаев вроде Ubuntu. Они используют окна без границы, растянутые на весь экран, то есть выглядят точно так же, как обычный полноэкранный режим. В режиме **fs_WINDOWED_STRETCHED** проекция растянута на весь экран.

Перечисление хранится в файле Main_Window.h.

Отметьте, что приложения на Android всегда получают весь экран, поэтому Square автоматически заменяет режимы **fs_WINDOWED** и **fs_FULLSCREEN_STRETCHED** на **fs_WINDOWED_STRETCHED**.
   
   
**Предыдущий файл:** [Класс Controller](05_Controller.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [Класс Resources](07_Resources.md)