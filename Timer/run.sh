#!/bin/bash

# Set up environment variables for Qt.
export QTDIR=$(brew --prefix qt@5)
export PATH=$QTDIR/bin:$PATH
export QMAKE=$QTDIR/bin/qmake

# Create the build directory if it doesn't exist.
mkdir -p build/obj
mkdir build/bin

# Navigate to the build directory.
cd build

# Generate the Makefile in the root directory.
qmake .. -o ../Makefile

# Navigate back to the root directory.
cd ..

# Remove old binary file.
rm -f ./Timer

# Build the project.
make

rm -f .qmake.stash

# Clear the terminal.
clear

# Run the project.
./build/bin/Timer