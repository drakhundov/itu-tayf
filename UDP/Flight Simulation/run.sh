#!/bin/bash

# Set up environment variables for Qt.
export QTDIR=$(brew --prefix qt@5)
export PATH=$QTDIR/bin:$PATH
export QMAKE=$QTDIR/bin/qmake
source ../init.sh

# Removing files from the previous build.
rm -rf build
rm -f Makefile

# Create the build directory if it doesn't exist.
mkdir -p build/obj
mkdir build/bin

# Generate the Makefile in the root directory.
qmake && make
rm -f .qmake.stash

# Clear the terminal.
clear

# Run the project.
./build/bin/FSS