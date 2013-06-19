﻿# класс Loader

## Общая информация

Класс Loader загружает и хранит ресурсы. Он не будет загружать уже загруженный ресурс и вернёт его сразу же. Объект этого класса хранится в объекте [Game](05_Game.md). Объект Game даёт указатель на объект Loader всем объектам [Screen](03_Screen.md), чтобы они могли использовать его функции.

## Функции

##### `SDL_Surface* load_image(string filename)`
Загружает изображение из файла с переданным именем и возвращает загруженный SDL_Surface.  
Если загрузка не удаётся, будет брошено исключение в виде **std::string**, содержащей описание ошибки.  
Если объявлена константа **[DBG_PRINT_IMAGE_LOADING](19_debug_h.md#dbg_print_image_loading)**, печатает сообщения о загрузке в лог.  

----
##### `Image* load_texture(string filename, bool keep_surface = true)`
Загружает изображение из файла с переданным именем и возвращает объект класса [Image](12_Image.md), содержащий индекс загруженной OpenGL-текстуры.  
Если загрузка не удаётся, будет брошено исключение в виде **std::string**, содержащей описание ошибки.  
Если параметр **keep_surface** равен **true**, SDL_Surface не будет освобождён и тоже будет передан в возвращаемом объекте Image. В таком случае **load_image()** для переданного имени файла также будет возвращать этот SDL_Surface.  
(Заметьте, что получение прозрачности пикселей из OpenGL-текстуры может быть медленней, чем получение прозрачности из SDL_Surface. При этом SDL_Surface занимает лишнюю память, поскольку OpenGL хранит её собственную скрытую копию.) 
Если объявлена константа **[DBG_PRINT_IMAGE_LOADING](19_debug_h.md#dbg_print_image_loading)**, печатает сообщения о загрузке в лог.  

----
##### `TTF_Font* load_font(string fontname, int size)`
Загружает шрифт с заданным именем и размером и возвращает его. Функция ищет шрифт в папке C:\Windows\Fonts\\. Если там его нет, то она ищет его в папке res\fnt\ вашего проекта. Если его и там нет, будет брошено исключение в виде **std::string**.  
Если загрузка не удаётся, будет брошено исключение в виде **std::string**, содержащей описание ошибки.  

----
##### `Sprite load_sprite(string filename)`
Загружает заданный файл, создаёт объект [Sprite](13_Sprite.md), который содержит значения из этого файла и возвращает этого объект. Все кадры спрайта загружаются функцией **[load_texture()](09_Loader.md#image-load_texturestring-filename-bool-keep_surface--true)**.  
Если объявлена константа **[DBG_PRINT_SPRITE_LOADING](19_debug_h.md#dbg_print_sprite_loading)**, печатает сообщения о загрузке в лог.  

----
##### `bool free_image(string filename)`
Освобождает память, занятую SDL_Surface для файла с переданным именем и возвращает **true**. Если для переданного имени не найдено соответствующего SDL_Surface, возвращает **false**.  

----
##### `bool free_texture(string filename)`
Освобождает память, занятую OpenGL-текстурой для файла с переданным именем и возвращает **true**. Если для переданного имени не найдено соответствующей текстуры, возвращает **false**.  
(Заметьте, что если для файла с переданным именем хранится ещё и SDL_Surface, он не будет освобождён вместе с текстурой.)  

----
##### `bool free_font(string fontname, int size)`
Освобождает память, занятую шрифтом с переданными именем и размером и возвращает **true**. Если шрифт с переданными именем и размером не найден, возвращает **false**.  

----
##### `void free()`
Освобождает память, занятую всеми SDL_Surface, OpenGL-текстурами и шрифтами, которые хранятся в данный момент в объекте Loader.

## Формат файла .sprite

Первая строка содержит два целых числа: **frames** и **animspeed**.  
Каждая из остальных **frames** строк содержат строку и два целых числа: **filename x y**.  
**animspeed** — это интервал между двумя кадрами спрайта (измеряется в кадрах перерисовки экрана), **filename** указывает имя файла, в котором хранится кадр, а **x** и **y** указывают на сдвиг данного кадра по осям X и Y.  
   
   
**Предыдущий файл:** [класс Input](08_Input.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [класс Logger](10_Logger.md)