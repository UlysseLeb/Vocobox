#!/bin/bash
set -e

echo "Cleaning previous build..."
rm -rf CMakeCache.txt CMakeFiles Vocobox.component

echo "Configuring..."
cmake .

echo "Building..."
make

echo "Installing to ~/Library/Audio/Plug-Ins/Components/..."
cp -R Vocobox.component ~/Library/Audio/Plug-Ins/Components/

echo "Done. Restart your DAW to load the plugin."
