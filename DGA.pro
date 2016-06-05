#-------------------------------------------------
#
# Project created by Vardanyan Andranik 2015-09-29T10:58:05
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DGA
TEMPLATE = app
CONFIG += c++11
QMAKE_CXXFLAGS +=-fopenmp
LIBS +=-lgomp
LIBS += "../build-DGA-Desktop_Qt_5_4_2_MinGW_32bit2-Debug/debug/fun.dll"

SOURCES += main.cpp\
        mainwindow.cpp \
    population.cpp \
    evolution.cpp \
    algorithm.cpp \
    flags.cpp

HEADERS  += mainwindow.h \
    population.h \
    evolution.h \
    algorithm.h \
    flags.h \
    fun.h \
    fun_global.h

FORMS    += mainwindow.ui
