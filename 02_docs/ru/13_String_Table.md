﻿# Класс String_Table

## Общая информация

Класс String_Table — хранилище для строк, которые можно получить по ключу. Эти строки могут быть загружены из файла и сохранены в файл. Ключи могут ссылаться на другие ключи (то есть получать своё значение из этих ключей) и содержать места для параметров. В этих местах в значение подставляются передаваемые параметры.

## Функции  

##### `String_Table()`
Конструктор, создающий пустую таблицу.  

----
##### `String_Table(string filename)`
Конструктор, загружающий таблицу из файла с указанным именем.  

----
##### `void push_table(string table)`
Добавляет значения из файла с указанным именем в таблицу.  
Таблица не изменится, если файл не будет найден.  
(Если **[DEBUG_LOG_WARNINGS](22_settings_h.md#debug_log_warnings)** равняется 1, в лог-файл будут записываться предупреждения о неправильных или рекурсивных ключах, а также об отсутствии файла с указанным именем.)  
(Если **[DEBUG_LOG_STRING_TABLES](22_settings_h.md#debug_log_string_tables)** равняется 1, после загрузки будет в лог-файл будет записана вся таблица.)  

----
##### `string operator[](string key)`
Возвращает значение, соответствующее переданному ключу.  
Если ключу не соответствует значения, возвращается "".  

----
##### `string operator()(...)`
    string operator()(
     string key,
     string* s0 = 0, string* s1 = 0, string* s2 = 0, string* s3 = 0,
     string* ss = 0
    )
Возвращает значение, соответствующее переданному ключу. Если значение содержит последовательности %0%, %1%, %2% и т. д., они будут заменены значениями **s0**, **s1**, **s2** и т. д. **ss** — массив строк. Поэтому, %4% заменяется значением **ss[0]**, %5% — **ss[1]** и т. д.  
Если параметр не определён (то есть указатель равен 0), соответствующее место будет заменено "".  
Если ключу не соответствует значения, возвращается "".  

----
##### `void clear()`
Очищает таблицу.  

----
##### `void displace(string key, string new_value)`
Заменяет значение, соответствующее переданному ключу, значением **new_value**.  
(Не может быть ссылкой на другой ключ.)  

----
##### `void save_table(string filename)`
Сохраняет таблицу в файл с именем **filename** так, что она может быть позже загружена функцией **[push_table()](13_String_Table.md#void-push_tablestring-table)**.  
Ссылки не сохраняются.

## Переменные  

##### `static String_Table unicode`
Содержит специальные символы кодировки Unicode.  
Использование: `String_Table::unicode["1000"]`.  
(По умолчанию, таблица загружается из файла unicode.txt в папке с локализацией. Вы можете изменить имена файлов (или убрать загрузку файла unicode.txt) в функции **Global::load_string_tables()** (объявленной в load_string_tables.h).)  

----
##### `static String_Table translate`
Содержит пары ключ-значение из файла general.txt (и любых других файлов, из которых вы загрузите значения в эту таблицу в функции **Global::load_string_tables()**).  
Использование: `String_Table::translate["key"]` или `String_Table::translate("key", &string("Value 1"), &string("Value 2"))`.  
   
   
**Предыдущий файл:** [Класс Frame](12_Frame.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [Класс Window](14_Window.md)