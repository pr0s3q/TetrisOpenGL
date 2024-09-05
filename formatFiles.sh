#!/bin/bash

DIRECTORY="./Engine/include"

for file in "$DIRECTORY"/*.h; do
  if [ -e "$file" ]; then
    echo "Formatting $file"
    clang-format -i "$file"
  fi
done

DIRECTORY="./Engine/src"

for file in "$DIRECTORY"/*.cpp; do
  if [ -e "$file" ]; then
    echo "Formatting $file"
    clang-format -i "$file"
  fi
done

DIRECTORY="./TetrisOpenGL/include"

for file in "$DIRECTORY"/*.h; do
  if [ -e "$file" ]; then
    echo "Formatting $file"
    clang-format -i "$file"
  fi
done

DIRECTORY="./TetrisOpenGL/src"

for file in "$DIRECTORY"/*.cpp; do
  if [ -e "$file" ]; then
    echo "Formatting $file"
    clang-format -i "$file"
  fi
done

echo "All files formatted!"