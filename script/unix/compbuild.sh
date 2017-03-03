#!/bin/bash

# run cmake to generate Makefile contents
cd .build
rm -rf CMakeFiles CMakeCache.txt cmake_install.cmake Makefile

echo "build.sh: Generating Makefiles..."
cmake -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=./arm.cmake robot.cmake .. > /dev/null

# run make for the Makefile now
os=$(uname | tr '[:upper:]' '[:lower:]')
if [[ "$os" == *"cygwin"* ]]; then
    echo "build.sh: Recognized building for Windows..."
elif [[ "$os" == *"linux"* ]]; then
    echo "build.sh: Recognized building for Linux"
    source make.settings > /dev/null 2>&1
else
    echo "build.sh: Recognized building for *nix (assumption)"
    source make.settings > /dev/null 2>&1
fi

if [ "$1" = "-v" ]; then
    make VERBOSE=1 -j $PARALLELBUILD
else
    make -j8
fi

# Delete cmake files to keep Eclipse working
echo "build.sh: Deleting CMakeFiles..."
rm -rf CMakeFiles/

echo "build.sh: Re-naming outfile..."
rm FRCUserProgram
mv FRC FRCUserProgram

if [ -f "FRCUserProgram" ]; then
    echo "build.sh: Built successfully!"
    exit 0
else
    echo "build.sh: Build failed!"
    exit 1
fi

exit
