#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T09:48:28
#
#-------------------------------------------------
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Faml
TEMPLATE = app

#INCLUDEPATH += /usr/lib64/gcc/x86_64-pc-linux-gnu/4.8.4/include/g++-v4/x86_64-pc-linux-gnu/32

SOURCES += main.cpp\
        mainwindow.cpp \
    logwindow.cpp \
    famldb.cpp \
    settingswindow.cpp

HEADERS  += mainwindow.h \
    logwindow.h \
    famldb.h \
    settingswindow.h

FORMS    += mainwindow.ui \
    logwindow.ui \
    settingswindow.ui

CONFIG += mobility
MOBILITY = 

CC=clang
CXX=clang++

