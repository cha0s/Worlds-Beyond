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

PRE_TARGETDEPS += ../chi/lib/libchi.a
INCLUDEPATH += ../chi/src .

win32:INCLUDEPATH += /c/msys/1.0/mingw/3rdparty/include /c/QtSDK/Desktop/Qt/4.8.1/mingw/include

SOURCES += main.cpp

HEADERS += $$system('find ../chi/src -name "*.h"')

CONFIG += console
win32:QMAKE_LFLAGS += -static-libgcc -Wl,-subsystem,windows

LIBS += -L../chi/v8 -L../chi/lib -lchi -lboost_filesystem -lboost_regex -lboost_system
WITH_DEBUG_V8 {
	LIBS += -lv8-chid
}
else {
	LIBS += -lv8-chi
}
win32:LIBS += -L/c/msys/1.0/mingw/3rdparty/lib -lmingw32 -lSDLmain  -lws2_32 -lwsock32 -lwinmm
LIBS += -lSDL -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf

win32:OUT_DIR = obj/win32
unix:OUT_DIR = obj/unix

OBJECTS_DIR = $$OUT_DIR

unix:QMAKE_CXXFLAGS += -ansi -Werror
