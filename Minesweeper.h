#ifndef MINESWEEPER_H // Guards against double inclusion
#define MINESWEEPER_H

#include <QApplication>
#include <QCoreApplication>
#include <QGridLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPushButton>
#include <vector>


// Custom QPushButton to represent a cell in Minesweeper
class Cell : public QPushButton {
    Q_OBJECT // Enables signal-slot mechanism
public:
    using QPushButton::QPushButton; // Inherits QPushButton constructors
    // Sets the cell's row and column in the grid
    void setCoordinates(int row, int col) { this->row = row; this->col = col; }
    // Returns the cell's row
    int getRow() const { return row; }
    // Returns the cell's column
    int getCol() const { return col; }

protected:
    // Custom mouse press event to handle right-clicks
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::RightButton) {
            emit rightClicked(); // Emits rightClicked signal on right click
        } else {
            QPushButton::mousePressEvent(event); // Default behavior for other clicks
        }
    }

signals:
    void rightClicked(); // Signal emitted on right click

private:
    int row, col; // Cell coordinates
};

// Main game class
class MinesweeperGame : public QMainWindow {
    Q_OBJECT

public:
    MinesweeperGame(QWidget *parent = nullptr); // Constructor
    ~MinesweeperGame(); // Destructor

private:
    void cellRightClicked(int row, int column); // Slot for handling right clicks
    void setupBoard(); // Initializes the game board
    void resetGame(); // Resets the game to its initial state
    void revealCell(int row, int column); // Reveals a cell
    void checkWinCondition(); // Checks if the win condition is met
    void revealMines(int r, int c); // Reveals all mines (used when game is over)
    void cellClicked(int row, int column); // Slot for handling cell clicks
    void handleGameOver(bool won); // Handles game over logic
    int countAdjacentMines(int row, int column); // Counts mines adjacent to a cell

    QGridLayout *gridLayout; // Layout for the grid of buttons
    QVector<QVector<Cell*>> buttons; // 2D array of cell buttons
    QVector<QVector<bool>> mines; // 2D array indicating mine positions
    QVector<QVector<bool>> flags; // 2D array indicating flag positions
    const int rows = 16; // Number of rows in the grid
    const int columns = 30; // Number of columns in the grid
    const int totalMines = 99; // Total number of mines
    int flagsPlaced = 0; // Number of flags currently placed
};

#endif // MINESWEEPERGAME_H
