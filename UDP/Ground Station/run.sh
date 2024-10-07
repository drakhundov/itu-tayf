#!/bin/bash

# Set up environment variables for Qt.
export QTDIR=$(brew --prefix qt@5)
export PATH=$QTDIR/bin:$PATH
export QMAKE=$QTDIR/bin/qmake
source ../init.sh

# Create the build directory if it doesn't exist.
mkdir -p build/obj
mkdir build/bin

# Create a directory for backups if doesn't exist.
mkdir backup

# Generate the Makefile in the root directory.
qmake && make
rm -f .qmake.stash
rm -f moc*

# Clear the terminal.
clear

# Run the project.
./build/bin/GSS