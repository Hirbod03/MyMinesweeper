// Author: Hirbod Hosseini (251234419) 
// Description of file contents: Minesweeper header files
// Date: Feb 2nd, 2024

#ifndef MINESWEEPER_H // Guards against double inclusion
#define MINESWEEPER_H

#include <QApplication>
#include <QCoreApplication>
#include <QGridLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include "Cell.h"

// Main game object
class Minesweeper : public QMainWindow {
    Q_OBJECT

public:
    Minesweeper(QWidget *parent = nullptr); // Constructor
    ~Minesweeper(); // Deconstructor

private:
    void cellClicked(int row, int column); // Slot for handling cell clicks
    void cellRightClicked(int row, int column); // Slot for handling right clicks
    void checkWinCondition(); // Checks if the win condition is met
    void resetGame(); // Resets the game to its initial state
    void revealCell(int row, int column); // Reveals a cell
    void revealMines(int r, int c); // Reveals all mines (used when game is over)
    void setupBoard(); // Initializes the game board
    void handleGameOver(bool won); // Handles game over logic
    int countAdjacentMines(int row, int column); // Counts mines adjacent to a cell

    QGridLayout *gridLayout; // Layout for the grid of buttons
    QVector<QVector<Cell*>> buttons; // 2D array of cell buttons
    QVector<QVector<bool>> mines; // 2D array indicating mine positions
    QVector<QVector<bool>> flags; // 2D array indicating flag positions
    const int ROWS = 16; // Number of rows in the grid
    const int COLUMNS = 30; // Number of columns in the grid
    const int TOTALMINES = 99; // Total number of mines
    int flagsPlaced = 0; // Number of flags placed at initial game state
};

#endif // MINESWEEPERGAME_H
