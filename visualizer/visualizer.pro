QT       += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = visualizer
TEMPLATE = app

LIBS += -lgdal

SOURCES += main.cpp\
        princ.cpp \
        glarea.cpp \
    dem.cpp

HEADERS  += princ.h \
        glarea.h \
    dem.h

FORMS    += princ.ui

RESOURCES += \
    visualizer.qrc
