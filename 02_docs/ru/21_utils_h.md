# Файл utils.h

## Общая информация

Файл utils.h содержит все полезные функции, использующиеся различными классами.  
В нём есть функции:
* для работы с SDL_Surface;
* для отрисовки текстур и прямоугольников;
* для того, чтобы узнать, является ли число степенью двойки;
* для нахождения ближайшей степени двойки, большей заданного числа;
* для того, чтобы узнать, существует ли файл с заданным именем;
* для чтения строк из заданного потока;
* для работы с числами, строками и Unicode;
* для нахождения кратчайшего пути с помощью алгоритма A*.

## Функции  

##### `Uint32 getpixel(SDL_Surface* surface, int x, int y)`
Возвращает четырёхбайтовое целое, содержащее информацию о цвете и прозрачности пикселя.  
Пиксель берётся из точки **x**, **y** изображения **surface**.  

----
##### `Uint8 get_color_r(SDL_Surface* surface, int x, int y)`
Возвращает Red-компоненту пикселя (0-255).  
Пиксель берётся из точки **x**, **y** изображения **surface**.  

----
##### `Uint8 get_color_g(SDL_Surface* surface, int x, int y)`
Возвращает Green-компоненту пикселя (0-255).  
Пиксель берётся из точки **x**, **y** изображения **surface**.  

----
##### `Uint8 get_color_b(SDL_Surface* surface, int x, int y)`
Возвращает Blue-компоненту пикселя (0-255).  
Пиксель берётся из точки **x**, **y** изображения **surface**.  

----
##### `Uint8 get_color_a(SDL_Surface* surface, int x, int y)`
Возвращает прозрачность пикселя (0-255, где 0 означает полную прозрачность, а 255 — непрозрачность).  
Пиксель берётся из точки **x**, **y** изображения **surface**.  

----
##### `SDL_Surface* create_surface(int w, int h, int bits = 32)`
Возвращает новый SDL_Surface, созданный с заданными параметрами.  

----
##### `SDL_Surface* create_surface(SDL_Surface* to_replace, int w, int h, int bits = 32)`
Возвращает новый SDL_Surface, созданный с заданными параметрами, который заменяет SDL_Surface, переданный параметром **to_replace**.  

----
##### `Frame* surface_to_texture(SDL_Surface* src, bool delete_after_transform = true)`
Преобразует заданный SDL_Surface **src** в текстуру OpenGL и возвращает объект [Frame](12_Frame.md), содержащий указатель на её идентификатор.  
Если **delete_after_transform** равняется **true**, **src** будет удалён после преобразования.  

----
#### `void draw_frame(...)`

    void draw_frame(
     Frame& frame,
     float x, float y,
     float alpha = 1.0f, float angle = 0, bool center = false
    )
Отрисовывает переданный Frame на экране в указанной позиции, с указанной прозрачностью и повёрнутый на указанный угол. Если **center** равняется **true**, центр текстуры будет в переданной координате.

----
    void draw_frame(
     Frame& frame,
     float x, float y,
     SDL_Color blend, float alpha = 1.0f,
     float angle = 0, bool center = false
    )
Отрисовывает переданный Frame на экране в указанной позиции, с указанной прозрачностью и повёрнутый на указанный угол. Он будет смешан с указанным цветом. Если **center** равняется **true**, центр текстуры будет в переданной координате.

----
    void draw_frame(
     Frame& frame,
     float x, float y, float w, float h,
     float alpha = 1.0f, float angle = 0, bool center = false
    )
Отрисовывает переданный Frame на экране в указанной позиции и с указанными шириной и высотой, с указанной прозрачностью и повёрнутый на указанный угол. Если **center** равняется **true**, центр текстуры будет в переданной координате.

----
    void draw_frame(
     Frame& frame,
     float x, float y, float w, float h,
     SDL_Color blend, float alpha = 1.0f,
     float angle = 0, bool center = false
    )
Отрисовывает переданный Frame на экране в указанной позиции и с указанными шириной и высотой, с указанной прозрачностью и повёрнутый на указанный угол. Он будет смешан с указанным цветом. Если **center** равняется **true**, центр текстуры будет в переданной координате.

----
#### `void draw_texture(...)`

    void draw_texture(
     float x, float y, float w, float h,
     bool center = false
    )
Отрисовывает закреплённую текстуру OpenGL на экране в указанной позиции (необходимо также передать её оригинальную ширину и высоту). Если **center** равняется **true**, центр текстуры будет в переданной координате.  

----
    void draw_texture(
     float x, float y, float w, float h,
     float nw, float nh,
     float angle = 0, bool center = false
    )
Отрисовывает закреплённую текстуру OpenGL на экране в указанной позиции (необходимо также передать её оригинальную ширину и высоту), растянутую до размеров **nw** и **nh** и повёрнутую на угол **angle**. Если **center** равняется **true**, центр текстуры будет в переданной координате.  

----
    void draw_texture(
     float W, float H,                          //ширина и высота самой текстуры
     float px, float py, float pw, float ph,    //позиция и размер отрисовываемой части
     float nx, float ny, float nw, float nh,    //позиция на экране и новый размер
     float angle, bool center = false           //угол поворота и установка по центру
    )
Отрисовывает часть закреплённой текстуры OpenGL на экране в указанной позиции (необходимо также передать её оригинальную ширину и высоту), растянутую до размеров **nw** и **nh** и повёрнутую на угол **angle**. Если **center** равняется **true**, центр текстуры будет в переданной координате. Часть берётся из точки **px**, **py**, а её ширина и высота будут равны **pw** и **ph** соответственно.  

----
##### `void draw_rectangle(int x, int y, int w, int h)`
Отрисовывает прямоугольник заданных размеров в указанной точке.  

----
##### `unsigned int nearest2(unsigned int a)`
Возвращает ближайшую степень двойки, большую или равную **a**.  

----
##### `bool is_power2(unsigned int a)`
Возвращает **true**, если **a** является степенью двойки.  

----
##### `bool file_exists(const char* name)`
##### `bool file_exists(string& name)`
Возвращает **true**, если файл с указанным именем существует.  

----
##### `void read_file(stringstream& destination, const char* name)`
##### `void read_file(stringstream& destination, string& name)`
Читает всё содержимое файла с указанным именем в поток std::stringstream **destination**.

----
##### `string read_string(ifstream&)`
Возвращает строку, считанню из переданного потока ввода. Если строка начинается с символа **"**, то функция считывает всё до следующего символа **"**. В противном случае пробельные символы будут считаться концом строки.  

----
##### `bool delete_file(const char* name)`
##### `bool delete_file(string& name)`
Удаляет файл с указанным именем и возвращает **true**, если это было успешно.

----
##### `void itoa(int i, char* buf, int base = 10)`
Записывает число **i** в **buf** в указанной системе счисления **base**.

----
##### `int atoi(const char* buf)`
Читает число из **buf** и возвращает его.

----
##### `int to_int(string)`
Читает число из строки и возвращает его. Пропускает все нецифровые символы (кроме **'+'** и **'-'** перед самим числом).  

----
##### `string to_string(int v, int base = 10)`
Возвращает строку, содержащую запись числа **v** в системе счисления **base**.  

----
##### `string unichar(Uint16 code)`
Возвращает строку, содержащую символ(ы), соответствующие указанному коду символа **code** в Unicode.  
(Использует вашу [String_Table::unicode](13_String_Table.md#static-string_table-unicode).)  

----
##### `bool letters_equal(string a, string b)`
Возвращает **true**, если строки **a** и **b** одинаковы. Считает строчные и заглавные буквы одинаковыми (например, **"FATE"**, **"fate"** и **"FaTe"** считаются одинаковыми).  

----
##### `string thousands(int n)`
Возвращает строку, представляющую число **n**, в котором тысячи записываются как «K» (например, 5000 станет  "5K").  

----
##### `stack<int> A_star(...)`
   stack<int> A_star(
    int start_x, int start_y,
    int target_x, int target_y,
    vector< vector<bool> >& obstacles,
    int usual = 10, int diagonal = 14
   )
Реализует алгоритм A*. Возвращает **stack** индексов точек, из которых состоит путь между точками **(start_x, start_y)** и **(target_x, target_y)**. Если пути нет, возвращается пустой **stack**. Параметр **obstacles** должен содержать **true** в точках, которые нельзя пройти, параметры **usual** и **diagonal** указывают «цену» ходов. (горизонтальные и вертикальные стоят **usual**, а диагональные — **diagonal**).  
   
   
**Предыдущий файл:** [Классы wstream и safe_wstream](20_wstreams.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [settings.h](22_settings_h.md)