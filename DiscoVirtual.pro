#-------------------------------------------------
#
# Project created by QtCreator 2017-05-30T20:18:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DiscoVirtual
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    archivo.cpp \
    bloquearchivo.cpp \
    bloquefolder.cpp \
    discovirtual.cpp \
    fileentry.cpp \
    files.cpp \
    input.cpp \
    masterblock.cpp

HEADERS  += mainwindow.h \
    archivo.h \
    bloquearchivo.h \
    bloquefolder.h \
    discovirtual.h \
    fileentry.h \
    files.h \
    input.h \
    masterblock.h

FORMS    += mainwindow.ui \
    input.ui
