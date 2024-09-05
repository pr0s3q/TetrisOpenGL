#!/bin/bash

DIRECTORY="./Engine/include/Engine"

for file in "$DIRECTORY"/*.hpp; do
  if [ -e "$file" ]; then
    echo "Formatting $file"
    clang-format -style=file -i "$file"
  fi
done

DIRECTORY="./Engine/src"

for file in "$DIRECTORY"/*.cpp; do
  if [ -e "$file" ]; then
    echo "Formatting $file"
    clang-format -style=file -i "$file"
  fi
done

DIRECTORY="./TetrisOpenGL/include/Tetris"

for file in "$DIRECTORY"/*.hpp; do
  if [ -e "$file" ]; then
    echo "Formatting $file"
    clang-format -style=file -i "$file"
  fi
done

DIRECTORY="./TetrisOpenGL/src"

for file in "$DIRECTORY"/*.cpp; do
  if [ -e "$file" ]; then
    echo "Formatting $file"
    clang-format -style=file -i "$file"
  fi
done

echo "All files formatted!"