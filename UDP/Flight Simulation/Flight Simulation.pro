QT += network

TARGET = build/bin/FSS
TEMPLATE = app
CONFIG -= app_bundle

SOURCES += src/main.cpp \
           src/UDPCommunicator.cpp
           
HEADERS += include/UDPCommunicator.h \
           include/Data.h

INCLUDEPATH += include
OBJECTS_DIR = build/obj