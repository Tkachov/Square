# Разработка под Android

## Общая информация

Square использует нетронутую версию официального порта SDL 2, но проект-шаблон Square для Android отличается от проекта-шаблона SDL 2. Вам нужно будет настроить его немного под собственные нужды. В этом файле содержится информация, которая может оказаться вам полезной.

## Создание проекта

1. Скопируйте папку *01_android_project* и переименуйте как хочется.
2. Скопируйте папки SDL в папку *<project>/jni*.
3. Скопируйте папку *src* из папки *00_template* в папку *<project>/jni*.
4. Добавьте свои исходные файлы в файл *<project>/jni/src/Android.mk*.
5. Скопируйте ресурсы приложения в папку *<project>/assets*.

Заметьте, что вам нужны будут папки SDL. Можете взять [мои](https://dl.dropboxusercontent.com/u/37122166/Square/Square_Android_SDL_folders.zip) или собрать их вручную.

Чтобы сделать приложение, вам нужно будет скомпилировать исходный код на C++, используя скрипт *ndk-build*, поставляющийся вместе с Android NDK, а потом пересобрать приложение на Android (например, через Eclipse).

## Настройка ориентации экрана

Шаблон и примеры Square используют ландшафтную ориентацию, но вы можете использовать любой режим, который захотите. Для этого нужна настройка "android:screenOrientation" в файле AndroidManifest.xml.

Поддерживаемые режимы перечислены в [официальной документации по Android](http://developer.android.com/guide/topics/manifest/activity-element.html#screen). Заметьте, что некоторые из них требуют определённый уровень Android API, указываемый в тэге uses-sdk в том же файле.

## Падение при повороте экрана

При смене ориентации экрана приложение может упасть. Оно *не упадёт*, если настройка "configChanges" в файле AndroidManifest.xml будет содержать настройку "orientation". Если вы не используете режимы "landscape", "portrait" или "locked", вам всё равно не стоит убирать эту настройку из "configChanges".

## Поведение полноэкранного режима

Полноэкранный режим в SDL на Android несколько отличается от такового на Windows/Ubuntu. Вы в любом случае получаете весь экран. Поэтому Square автоматически сменяет оконный режим на «поддельный» полноэкранный режим, в котором изображение выбранного размера растягивается на весь экран (в «настоящем» полноэкранном режиме приложение занимает лишь верхний левый угол экрана, а оставшаяся часть выглядит пустой).

## Текстовые файлы

Каждое приложение на Android имеет свой «sandbox». Используя файлы с относительным путём, вы сохраняете их в нём. Это значит, что другие приложения не смогут добраться до этих файлов. Из-за этого может быть сложно читать лог-файлы, но единственным решением этого являются файлы с абсолютным путём. Square использует относительные пути, так что если вы хотите проще добираться до лог-файлов на Android, вам нужно будет выбрать подходящее для вас решение.

Также, из-за этого в Square 0.3.0 и появились классы [wstream](20_wstreams.md) и safe_wstream. Вы не можете работать с файлами из «sandbox» через стандартные функции ввода/вывода, но SDL предоставляет для этого интерфейс. Классы wstream немного напоминают упрощённый std::ofstream. safe_wstream сбрасывает на диск все данные сразу же (поэтому, если приложение упадёт, файл будет содержать всё, что должно было быть записано до падения), хотя может быть из-за этого немного медленнее, чем wstream (который не гарантирует, что весь вывод будет записан в файл в случае падения).
   
   
**Предыдущий файл:** [Compiling](23_Compiling.md)  
**[Содержание](00_Contents.md)**