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

SOURCES += main.cpp\
        mainwindow.cpp \
    population.cpp \
    evolution.cpp \
    algorithm.cpp \
    test.cpp

HEADERS  += mainwindow.h \
    population.h \
    evolution.h \
    algorithm.h \
    test.h

FORMS    += mainwindow.ui
