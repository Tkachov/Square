LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
SDL_IMAGE_PATH := ../SDL2_image-2.0.0
SDL_TTF_PATH = ../SDL2_ttf-2.0.12

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/$(SDL_IMAGE_PATH) \
	$(LOCAL_PATH)/$(SDL_TTF_PATH)

LOCAL_CFLAGS := -DANDROID_NDK \
                -DDISABLE_IMPORTGL \
		-DDEBUG_MODE

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	main.cpp \
	importgl.c \
	Engine/Application.cpp \
	Engine/Controller.cpp \
	Engine/Input.cpp \
	Engine/Logger.cpp \
	Engine/Loop.cpp \
	Engine/Main_Window.cpp \
	Engine/Resources.cpp \
	Engine/State.cpp \
	Engine/utils.cpp \
	Engine/Data/Frame.cpp \
	Engine/Data/safe_wstream.cpp \
	Engine/Data/String_Table.cpp \
	Engine/Data/wstream.cpp \
	Engine/Entities/Button.cpp \
	Engine/Entities/Entity.cpp \
	Engine/Entities/Fade.cpp \
	Engine/Entities/Screen.cpp \
	Engine/Entities/Sprite.cpp \
	Engine/Entities/Text.cpp \
	Engine/Entities/Window.cpp \
	Engine/Global/load_string_tables.cpp \
	Engine/Global/ScreenID.cpp \
	screens/Index_Screen.cpp \

LOCAL_CPPFLAGS += -fexceptions

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf GL

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
