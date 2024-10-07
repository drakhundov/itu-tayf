QT += core gui widgets
QT += network

TARGET = build/bin/GSS
TEMPLATE = app
CONFIG -= app_bundle
CONFIG += qt gui

SOURCES += src/main.cpp \
           src/mainwindow.cpp \
           src/UDPCommunicator.cpp \
           src/button_styling.cpp \
           src/CSVBackUp.cpp

HEADERS += include/mainwindow.h \
           include/UDPCommunicator.h \
           include/button_styling.h \
           include/Data.h \
           include/CSVBackUp.h

INCLUDEPATH += include
OBJECTS_DIR = build/obj