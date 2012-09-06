#-------------------------------------------------
#
# Project created by QtCreator 2010-11-18T08:15:47
#
#-------------------------------------------------

TARGET = wb
DESTDIR = ..
TEMPLATE = app

CONFIG -= qt
CONFIG += gui exceptions

!debug {
	CONFIG += silent
}

INCLUDEPATH += /usr/include/qt4

win32:INCLUDEPATH += /c/msys/1.0/mingw/3rdparty/include /c/QtSDK/Desktop/Qt/4.8.1/mingw/include

SOURCES += \
	\
	main.cpp \
	\
	wbv8.cpp Exception.cpp ObjectWrap.cpp \
	\
	Graphics/GraphicsSystem.cpp Graphics/Image.cpp Graphics/Screen.cpp \
#	Graphics/Qt/QtGraphicsSystem.cpp Graphics/Qt/QtImage.cpp \
	Graphics/SDL/SdlGraphicsSystem.cpp Graphics/SDL/SdlImage.cpp \
	Graphics/SDL/SdlScreen.cpp \
	\
	Input/SDL/SdlInput.cpp Input/SDL/SdlInputSystem.cpp Input/Input.cpp \
	Input/InputSystem.cpp \
	\
	Script/ScriptSystem.cpp Script/Script.cpp \
	Script/v8/Music_v8.cpp Script/v8/Sample_v8.cpp Script/v8/SoundSystem_v8.cpp \
	Script/v8/Input_v8.cpp Script/v8/GraphicsSystem_v8.cpp \
	Script/v8/Counter_v8.cpp Script/v8/System_v8.cpp \
	Script/v8/v8ScriptSystem.cpp Script/v8/TimingSystem_v8.cpp \
	Script/v8/Screen_v8.cpp Script/v8/InputSystem_v8.cpp Script/v8/v8Script.cpp \
	Script/v8/Image_v8.cpp \
	\
	Sound/Music.cpp Sound/Sample.cpp \
	Sound/SDL/SdlMusic.cpp Sound/SDL/SdlSample.cpp Sound/SDL/SdlSoundSystem.cpp \
	Sound/SoundSystem.cpp \
	\
	System/System.cpp \
#	System/Qt/QtSystem.cpp \
	System/SDL/SdlSystem.cpp \
	\
	Timing/Counter.cpp Timing/TimingSystem.cpp \
#	Timing/Qt/QtCounter.cpp Timing/Qt/QtTimingSystem.cpp \
	Timing/SDL/SdlCounter.cpp Timing/SDL/SdlTimingSystem.cpp

HEADERS += \
	\
	wb-global.h wbv8.h Exception.h Factory.h ObjectWrap.h ResourceCounter.h \
	ResourceManager.h \
	\
	Graphics/Floodfill.h Graphics/GraphicsSystem.h Graphics/Image.h \
	Graphics/Screen.h \
#	Graphics/Qt/QtGraphicsSystem.h Graphics/Qt/QtImage.h \
	Graphics/SDL/SdlGraphicsSystem.h Graphics/SDL/SdlImage.h \
	Graphics/SDL/SdlScreen.h \
	\
	Input/Input.h Input/InputSystem.h \
	Input/SDL/SdlInput.h Input/SDL/SdlInputSystem.h \
	\
	Script/Script.h Script/ScriptSystem.h \
	Script/v8/Counter_v8.h Script/v8/GraphicsSystem_v8.h Script/v8/Image_v8.h \
	Script/v8/InputSystem_v8.h Script/v8/Input_v8.h Script/v8/Music_v8.h \
	Script/v8/Sample_v8.h Script/v8/Screen_v8.h Script/v8/SoundSystem_v8.h \
	Script/v8/System_v8.h Script/v8/TimingSystem_v8.h Script/v8/v8Script.h \
	Script/v8/v8ScriptSystem.h \
	\
	Sound/Music.h Sound/Sample.h Sound/SoundSystem.h \
	Sound/SDL/SdlMusic.h Sound/SDL/SdlSample.h Sound/SDL/SdlSoundSystem.h \
	\
	System/System.h \
#	System/Qt/QtSystem.h \
	System/SDL/SdlSystem.h \
	\
	Timing/Counter.h Timing/TimingSystem.h \
#	Timing/Qt/QtCounter.h Timing/Qt/QtTimingSystem.h \
	Timing/SDL/SdlCounter.h Timing/SDL/SdlTimingSystem.h

#HEADERS += $$system('find ../lib/src -name "*.h"')

win32:CONFIG += console
win32:QMAKE_LFLAGS += -static-libgcc -Wl,-subsystem,windows

LIBS += -L../lib/v8
LIBS += -lboost_filesystem -lboost_regex -lboost_system
WITH_DEBUG_V8 {
	LIBS += -lv8-wbd
}
else {
	LIBS += -lv8-wb -lv8_snapshot-wb
}
win32:LIBS += -L/c/msys/1.0/mingw/3rdparty/lib -lmingw32 -lSDLmain  -lws2_32 -lwsock32 -lwinmm
LIBS += -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf

win32:OUT_DIR = obj/win32
unix:OUT_DIR = obj/unix

OBJECTS_DIR = $$OUT_DIR

unix:QMAKE_CXXFLAGS += -ansi -Werror
