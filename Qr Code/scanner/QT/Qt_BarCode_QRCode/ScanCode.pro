#-------------------------------------------------
#
# Project created by QtCreator 2012-10-14T11:49:19
#
#-------------------------------------------------

QT       += core gui

TARGET = ScanCode
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    use_cvsnakeimage.cpp

HEADERS  += mainwindow.h \
    use_cvsnakeimage.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv

LIBS += /usr/local/lib/*.so
