﻿# Поток программы

## Бесконечный цикл

В C и C++ точкой входа для приложения является функция **main()**, объявленная в файле main.cpp. В ней содержится бесконечный цикл, сделанный для того, чтобы вы могли перезапускать игру без необходимости завершения процесса приложения. Это может быть использовано для переключения языка или режима графики на лету.

Используйте метод **[Controller::restart_loop()](05_Controller.md#void-restart_loopbool-keep_state)**, чтобы перезапускать приложение. Он очистит ресурсы игры и перезапустит его с экрана, на котором был вызван (вы также можете запустить игру с начального экрана, не сохраняя текущего состояния, передав в этот метод значение **false**).

Если произойдёт необработанное исключение или игра будет остановлена методом **[Controller::stop_loop()](05_Controller.md#void-stop_loop)**, то бесконечный цикл в функции **main()** прервётся и приложение остановится.

## Обновление ввода и перерисовка экрана

Бесконечный цикл, обрабатывающий пользовательский ввод и перерисовывающий экран разработан так, чтобы игра работала как можно плавнее в любой ситуации. Вы можете настроить его через константы **TICKS_PER_SECOND** и **MAX_FRAMESKIP**, объявленные в файле [settings.h](22_settings_h.md).

Основная идея этого цикла заключается в том, чтобы разделить обработку ввода и перерисовку экрана. Если возможно, экран будет перерисован **TICKS_PER_SECOND** раз за секунду, но если это будет невозможно, некоторые кадры будут пропускаться. Цикл не может пропустить больше, чем **MAX_FRAMESKIP** кадров подряд и перерисует экран, если уже пропустил такое количество кадров. Перерисовка выполняется методом **redraw()**  класса [Screen](03_Screen.md), который вызывает методы **[redraw()](04_Entity.md#void-redrawint-x-int-y)** классов [Entity](04_Entity.md).

Ввод от пользователя обрабатывается специальным классом [Input](08_Input.md). Ввод может обрабатываться чаще, чем происходит перерисовка экрана, чтобы игра могла реагировать на действия пользователя быстрее. Текущие состояния клавиатуры и мыши хранятся в классе Input. Все его методы являются статичными, то есть вы можете вызвать их откуда захотите. Обновление состояния выполняется методом **update()** класса Screen, вызывающего функции **[update()](04_Entity.md#void-updateint-x-int-y)** классов Entity. Таким образом, все объекты Entity могут обновлять своё состояние (например, кнопка может среагировать на нажатие клавиши и выполнить какое-нибудь действие).
   
   
**Предыдущий файл:** [Общая информация](01_Overview.md)  
**[Содержание](00_Contents.md)**  
**Следующий файл:** [Класс Screen](03_Screen.md)