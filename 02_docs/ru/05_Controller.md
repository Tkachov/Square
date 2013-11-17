# Класс Controller

## Общая информация

Класс Controller отвечает за некоторые общие действия. Указатель на объект этого класса передаётся каждому [Entity](04_Entity.md), чтобы они могли использовать Controller, если потребуется.

## Функции  

##### `void stop_loop()`
Останавливает цикл приложения.  

----
##### `void restart_loop(bool keep_state)`
Перезапускает приложение.  
Может использоваться для применения изменений в настройках (если эти изменения требуют перезапуска).
Если значение **keep_state** равно **true**, то объект [State](09_State.md) будет сохранён, то есть значения «постоянных» переменных после перезапуска останется прежним.  

----
##### `void open_screen(Screen* screen)`
Открывает переданный Screen **screen**.  

----
##### `void open_screen(ScreenID sid, bool recreate = false)`
Открывает Screen с указанным ScreenID **sid**.  
Создаёт новый экземпляр объекта, если значение **recreate** равно **true**.  
Функция работает только если вы добавили свой класс, наследующий Screen, в функцию **[create_screen()](03_Screen.md#screenid)**!   

----
##### `void save(string filename)`
Сохраняет текущее состояние в файл с именем **filename** в подпапке «saves».  

----
##### `void load(string filename)`
Загружает состояние из файл с именем **filename** из подпапки «saves».  
 
----
##### `string get_option(string key)`
Возвращает значение настройки с именем **key**.  

----
##### `void set_option(string key, string value)`
Заменяет значение настройки **key** значением **value**.

----
##### `void save_options()`
Сохраняет настройки в файл **[CONFIG_FILENAME](22_settings_h.md#config_filename)**, если эта константа определена.  
   
   
**Предыдущий файл:** [Класс Entity](04_Entity.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [Класс Main_Window](06_Main_Window.md)