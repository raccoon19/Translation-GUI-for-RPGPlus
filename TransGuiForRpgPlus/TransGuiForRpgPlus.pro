#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T15:17:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TransGuiForRpgPlus
TEMPLATE = app


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/tabview.cpp \
    src/util.cpp

HEADERS  += \
    src/mainwindow.h \
    src/tabview.h \
    src/util.h

FORMS    += \
    resources/mainwindow.ui \
    resources/tabview.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../yaml-cpp/build/release/ -lyaml-cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../yaml-cpp/build/debug/ -lyaml-cpp
else:unix: LIBS += -L$$PWD/../yaml-cpp/build/ -lyaml-cpp

INCLUDEPATH += $$PWD/../yaml-cpp/include
DEPENDPATH += $$PWD/../yaml-cpp/include
