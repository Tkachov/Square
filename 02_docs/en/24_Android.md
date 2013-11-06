# Developing for Android

## General

Square is using virgin official SDL 2 port code, but Square template project for Android differs from SDL 2 template project. You'll need to customize it a bit for your own needs. There is some information you may find useful.

## Creating the project

1. Copy *01_android_project* directory and rename it as you wish.
2. Copy SDL's directories into *<project>/jni* directory.
3. Copy *src* directory from *00_template* directory into the *<project>/jni* directory.
4. Edit *<project>/jni/src/Android.mk* to include your source files.
5. Copy all application's resources into *<project>/assets* directory.

Note that you'll need SDL's folders. You can use [mine](https://dl.dropboxusercontent.com/u/37122166/Square/Square_Android_SDL_folders.zip) or make them using SDL's development libraries.

To make an application, you'll have to build C++ source code using *ndk-build* script which is provided by Android's NDK and then rebuild Android application (using Eclipse or in other way).

## Setting screen orientation modes

Square's template and example projects are using landscape orientation, but you can use any mode you want to. This can be customized using "android:screenOrientation" setting of Android activity that is written in AndroidManifest.xml file.

All supported modes are described in [official Android documentation](http://developer.android.com/guide/topics/manifest/activity-element.html#screen). Note that some of them require certain Android API level which can be in uses-sdk tag in the same file.

## Crash on screen rotation

Application can crash on screen orientation change. It *will not* if "configChanges" setting of Android activity in AndroidManifest.xml file will contain "orientation" option. If you are not using "landscape", "portrait" or "locked" mode, you should not remove "orientation" option from "configChanges".

## Fullscreen mode behaviour

SDL's fullscreen on Android differs from fullscreen on Windows/Ubuntu a bit. You're getting whole screen in any case. That's why Square automatically changes windowed mode to “fake” fullscreen mode when desired surface is stretched onto screen (in “real” fullscreen mode the application just takes the top-left corner of the screen and all unused area looks empty).

## Text files

Android gives the “sandbox” to each application. When you're using files with relative path, they're saved in your application's sandbox. So, other applications can't access these files. It may be difficult to read log files because of that, but the only solution of that is using absolute paths. Square uses relative paths, so if you want to easily read those log files, you'll have to find a solution that is good for you.

That's actually the reason why Square 0.3.0 introduces [wstream](20_wstreams.md) and safe_wstream classes. You can't read or write to files in sandbox using standard input/output, but SDL has an interface for that. wstream classes are something like simplified std::ofstream. safe_wstream flushes all data instantly (so if application will crash, file will contain everything that has to be written before the crash), though it can be a bit slower than using wstream (which does not guarantees that all the information will be written in case of crash).
   
   
**Previous file:** [Compiling](23_Compiling.md)  
**[Contents](00_Contents.md)**