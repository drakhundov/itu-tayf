QT += network

TARGET = build/bin/FSS
TEMPLATE = app
CONFIG -= app_bundle

SOURCES += src/main.cpp \
           src/UDPCommunicator.cpp \
           src/Satellite.cpp
           
HEADERS += include/UDPCommunicator.h \
           include/Data.h \
           include/Satellite.h

INCLUDEPATH += include
OBJECTS_DIR = build/obj