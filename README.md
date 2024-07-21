# Hirbod's Minesweeper ![ms](https://github.com/user-attachments/assets/d24ec014-1a74-43c1-bd1e-8214afac69ba)


## Introduction
This project is a C++ implementation of the classic Minesweeper game. It features a graphical user interface (GUI) built with Qt framework and the classic Minesweeper gameplay experience with a modern touch.

## Features
- Customizable grid size and mine count (in the header file).
- Classic Minesweeper mechanics.
- Graphical representation of mines, flags, and explosions.
- Restart game feature.

## How to Play
- Left-click on a cell to reveal what is underneath it.
- Right-click on a cell to place a flag where you suspect a mine is located.
- The game ends when you reveal all cells without mines, or if you reveal a mine.

## Installation
To play the game, compile the source code using a C++ compiler with Qt support. Make sure all `.cpp` and `.h` files are included in the compilation, along with the resources in `resources.qrc`.

## Building the Game
1. Install Qt and a suitable C++ compiler.
2. Clone the repository to your local machine.
3. Navigate to the directory containing the `Minesweeper.pro` file.
4. Run `qmake` to generate the Makefile.
5. Compile the project by running `make`.

## Dependencies
- Qt 5.12 or later


