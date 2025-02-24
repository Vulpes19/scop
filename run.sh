#!/bin/bash

# Detect and run the executable
if [ -f "build/Debug/scop.exe" ]; then
    echo "Running Debug version"
    build/Debug/scop.exe
elif [ -f "build/Release/scop.exe" ]; then
    echo "Running Release version"
    build/Release/scop.exe
else
    echo "Executable not found. Please build the project first."
    exit 1
fi