﻿# класс String_Table

## Общая информация

Класс String_Table является контейнером для строк (класса **std::string**), которые можно получать используя ключ. Строки могут быть загружены из файла и сохранены в него. Ключи могут указывать на другие ключи (т.е. брать значение других ключей), а значения могут содержать места для параметров. В значение в этих местах будут вставлены любые параметры, которые вы передадите.

## Функции  

##### `String_Table()`
Констуктор, создаёт пустую таблицу.  

----
##### `String_Table(string filename)`
Конструтор, загружает пары ключ-значение из файла с переданным именем.  

----
##### `void push_table(string table)`
Добавляет в таблицу пары ключ-значение из файла с переданным именем.  
Если файл не будет найден, таблица не изменится.  
(Если объявлена константа **[DBG_PRINT_WARNINGS](19_debug_h.md#dbg_print_warnings)**, то в лог будут напечатаны предупреждения в случае если файл не будет найден или в нём будут неправильные или рекурсивные ключи.)  
(Если объявлена константа **[DBG_PRINT_STRING_TABLES](19_debug_h.md#dbg_print_string_tables)**, вся таблица будет напечатана в лог после загрузки файла.)  

----
##### `string operator[](string key)`
Возвращает значение, соответствующее переданному ключу.  
Возвращает "", если переданному ключу не соответствует никакого значения.  

----
##### `string operator()(string key, string* s0 = 0, string* s1 = 0, string* s2 = 0, string* s3 = 0, string* ss = 0)`
Возвращает значение, соответствующее переданному ключу. Если значение содержит подстроки %0%, %1%, %2% и т.д., то они будут заменены параметрами **s0**, **s1**, **s2** и т.д. **ss** — это массив строк. Таким образом, %4% будет заменено значением **ss[0]**, %5% — **ss[1]** и т.д.  
Если параметр не определён (т.е. указатель равен 0), в соответствующее место будет вставлено "".  
Возвращает "", если переданному ключу не соответствует никакого значения.  

----
##### `void clear()`
Удаляет из таблицы все пары ключ-значение.  

----
##### `void displace(string key, string new_value)`
Заменяет значение переданного ключа переданным **new_value**.  
(Значение не может быть ссылкой на другой ключ.)  

----
##### `void save_table(string filename)`
Сохраняет все пары ключ-значение в файл с переданным именем **filename** в таком формате, что он может быть загружен с помощью функции **[push_table()](07_String_Table.md#void-push_tablestring-table)**.  
Ссылки не сохраняются.

## Переменные  

##### `public static String_Table unicode`
Содержит специальные символы кодировки Unicode.  
Использование: `String_Table::unicode["1000"]`.  
(По умолчанию таблица загружается из файла unicode.txt из папки локализации. Вы можете изменить имена файлов (или отменить загрузку этого файла) в функции **Game::start()**.)  

----
##### `public static String_Table translate`
Содержит пары ключ-значение из general.txt (и других файлов, которые вы загрузите в таблицу в функции **Game::start()**).  
Использование: `String_Table::translate["key"]` или `String_Table::translate("key", string("Слово 1"), string("Слово 2"))`.  
   
   
**Предыдущий файл:** [Использование класса functor](06_Using_functors.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [класс Input](08_Input.md)