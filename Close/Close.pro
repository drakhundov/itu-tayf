QT += core gui widgets

TARGET = build/bin/Close
TEMPLATE = app
CONFIG -= app_bundle
CONFIG += qt gui

SOURCES += src/main.cpp \
           src/mainwindow.cpp

HEADERS += include/mainwindow.h

INCLUDEPATH += include
OBJECTS_DIR = build/obj