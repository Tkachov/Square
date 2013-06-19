﻿# класс Logger

## Общая информация

Класс Logger позволяет вам писать сообщения в лог-файлы и консоль из любого класса, который у вас есть.  
Он создаёт файл только когда он действительно нужен (т.е. когда первое сообщение было отправлено в объект Logger).  
Если вы компилируете проект в Debug, приложение также будет иметь окно консоли. Оно может быть использовано, чтобы узнать, при каких именно условиях сообщения поступают в лог.  

## Функции  

##### `template<class T> Logger& operator<<(const T& p)`
Записывает значение объекта класса **T** в файловый и консольный потоки.  
Возвращает ссылку на объект Logger, чтобы его можно было использовать как цепочку:  
`Logger::log << a << b << c << d << e;`  

----
##### `void start_session()`
Заканчивает предыдущую сессию (если она была начата) и удаляет старые лог-файлы.  

----
##### `void end_session()`
Заканичвает текущую сессию (если она была начата) и закрывает лог-файлы (чтобы что-нибудь другое могло их открыть).

## Переменные  

##### `static Logger log`
Закреплён за файлом log.txt и консольным потоком **cout**.  
Использование: `Logger::log << "сообщение";`.  

----
##### `static Logger err`
Закреплён за файлом errors.txt и консольным потоком **cerr**.  
Использование: `Logger::err << "ошибка";`.  
   
   
**Предыдущий файл:** [класс Loader](09_Loader.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [класс State](11_State.md)