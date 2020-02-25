QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visualizer
TEMPLATE = app

!win32{
    LIBS += -lglut -lGLU -lGL
}
win32{
    LIBS += -lGLU32\
            -lOpengl32
}

SOURCES +=  main.cpp\
            princ.cpp\
            glarea.cpp\
            mytruc.cpp\
            dem.cpp

HEADERS  += princ.h\
            glarea.h\
            mytruc.h\
            dem.h

FORMS    += princ.ui

RESOURCES += \
    visualizer.qrc
