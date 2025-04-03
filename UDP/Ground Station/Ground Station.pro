QT += core gui widgets
QT += network
QT += 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation

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

RESOURCES += assets.qrc

INCLUDEPATH += include
OBJECTS_DIR = build/obj