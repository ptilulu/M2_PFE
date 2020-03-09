QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visualizer
TEMPLATE = app

!win32{
    LIBS += -lglut -lGLU -lGL -lgdal
}
win32{
    LIBS += -lGLU32\
            -lOpengl32
}

SOURCES +=  main.cpp\
            princ.cpp\
            glarea.cpp\
            dem.cpp \
    terraindisplayer.cpp \
    commands.cpp \
    voxeldisplayer.cpp

HEADERS  += princ.h\
            glarea.h\
            dem.h \
    terraindisplayer.h \
    commands.h \
    voxeldisplayer.h

FORMS    += princ.ui \
    commands.ui

RESOURCES += \
    visualizer.qrc
