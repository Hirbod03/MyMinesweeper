#include "Minesweeper.h"

// Constructor: Sets up the game window and initializes the game board
MinesweeperGame::MinesweeperGame(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this); // Create a central widget for the QMainWindow
    gridLayout = new QGridLayout(centralWidget); // Create and set a grid layout for the central widget
    gridLayout->setSpacing(0); // Remove spacing between buttons
    gridLayout->setContentsMargins(0, 0, 0, 0); // Remove margins around the grid
    setCentralWidget(centralWidget); // Set the central widget
    setupBoard(); // Initialize the game board with buttons
    resetGame(); // Reset the game to start state
}

// Destructor: Handles clean-up, not explicitly defined here
MinesweeperGame::~MinesweeperGame() {}

// Initializes the game board with buttons
void MinesweeperGame::setupBoard() {
    mines.resize(rows); // Resize the vector to hold mine information
    flags.resize(rows); // Resize the vector to hold flag information
    buttons.resize(rows); // Resize the vector to hold rows of buttons
    srand(static_cast<unsigned>(time(nullptr))); // Initialize random seed
    for (int row = 0; row < rows; ++row) {
        mines[row].resize(columns, false); // Initialize mine positions to false
        flags[row].resize(columns, false); // Initialize flag positions to false
        buttons[row].resize(columns); // Resize each row to hold columns of buttons
        for (int column = 0; column < columns; ++column) {
            Cell *button = new Cell(this); // Create a new button
            button->setFixedSize(20, 20); // Set fixed size for buttons
            button->setCoordinates(row, column); // Assign coordinates to the button
            // Set button style
            // I didn't make this part I just asked gpt 3.5
            button->setStyleSheet("QPushButton {" "border: 1px solid #8f8f91;""border-radius: 0px;""background-color: #c0c0c0;""font-weight: bold;""color: black""}""QPushButton:pressed {""background-color: #f0f0f0;""}");
            gridLayout->addWidget(button, row, column); // Add button to the grid layout
            buttons[row][column] = button; // Store the button in the buttons vector

            // Connect button signals to slots
            connect(button, &QPushButton::clicked, this, [=]() { cellClicked(row, column); });
            connect(button, &Cell::rightClicked, this, [=]() { cellRightClicked(row, column); });
        }
    }
}

// Resets the game to its initial state
void MinesweeperGame::resetGame() {
    // Iterate over each cell to reset its state
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            buttons[row][column]->setEnabled(true); // Enable button
            buttons[row][column]->setIcon(QIcon()); // Clear any icons
            buttons[row][column]->setText(""); // Clear any text
            mines[row][column] = false; // Clear mine
            flags[row][column] = false; // Clear flag
        }
    }

    // Randomly place mines
    int minesPlaced = 0;
    while (minesPlaced < totalMines) {
        int row = rand() % rows;
        int column = rand() % columns;
        if (!mines[row][column]) { // Place a mine if there isn't already one
            mines[row][column] = true;
            ++minesPlaced;
        }
    }
}

// Counts the number of adjacent mines for a given cell
int MinesweeperGame::countAdjacentMines(int row, int column) {
    int count = 0;
    // Check all adjacent cells
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = column + j;
            // Ensure the cell is within bounds and has a mine
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns && mines[newRow][newCol]) 
                ++count;
        }
    }
    return count;
}

// Reveals the cell at the specified coordinates
void MinesweeperGame::revealCell(int row, int column) {
    if (row < 0 || row >= rows || column < 0 || column >= columns) return; // Bounds check
    Cell *button = buttons[row][column];
    if (button->isEnabled()) { // If the cell is not already revealed
        button->setEnabled(false); // Disable button to prevent further clicks
        int adjacentMines = countAdjacentMines(row, column); // Count adjacent mines
        if (adjacentMines > 0) { // If there are adjacent mines, display the count
            button->setText(QString::number(adjacentMines));
        } else {
            // If no adjacent mines, recursively reveal adjacent cells
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0)
                        continue; // Skip the current cell
                    else
                        revealCell(row + i, column + j);
                }
            }
        }
    }
}

// Handles right-clicks on cells for flagging or marking them
void MinesweeperGame::cellRightClicked(int row, int column) {
    Cell *button = buttons[row][column];
    if (button->isEnabled()) { // If the cell is not revealed
        if (button->text() == "?") {
            // Toggle off "?" mark
            button->setText("");
            button->setIcon(QIcon()); // Clear any icons
        } else if (flags[row][column]) {
            // Toggle on "?" mark if flagged
            button->setIcon(QIcon());
            button->setText("?");
            flags[row][column] = false;
        } else {
            // Flag the cell
            button->setText("");
            button->setIcon(QIcon(":/images/flag"));
            flags[row][column] = true;
        }
    }
}

// Reveals all mines except the one that was triggered
void MinesweeperGame::revealMines(int r, int c) {
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            if (mines[row][column] && (row != r || column != c))
                buttons[row][column]->setIcon(QIcon(":/images/bomb")); // Reveal the mine
        }
    }
}

// Handles cell click events
void MinesweeperGame::cellClicked(int row, int column) {
    Cell *button = buttons[row][column];
    if (flags[row][column] || button->text() == "?") return; // Ignore clicks on flagged or "?" marked cells
    if (mines[row][column]) {
        // If the cell contains a mine, trigger game over
        button->setIcon(QIcon(":/images/bomb_explode"));
        revealMines(row, column); // Reveal all mines, passes cordinate of current one so the image isn't overwritten
        handleGameOver(false); // Indicate loss
    } else 
        // Otherwise, reveal the cell
        revealCell(row, column);
    checkWinCondition(); // Check if the win condition is met
}


// Checks if the win condition (all non-mine cells revealed) is met
void MinesweeperGame::checkWinCondition() {
    int revealedCells = 0;
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            Cell *button = buttons[row][column];
            if (!button->isEnabled() && !mines[row][column]) 
                revealedCells++; // Count revealed non-mine cells
        }
    }
    if (revealedCells == (rows * columns - totalMines))
        handleGameOver(true); // If all non-mine cells are revealed, the player wins
}

// Displays a message box to indicate game over and asks if the user wants to play again
void MinesweeperGame::handleGameOver(bool won) {
    QMessageBox messageBox;
    messageBox.setWindowTitle(won ? "Congratulations!" : "Game Over!");
    messageBox.setText(won ? "You've won the game!" : "You've hit a mine!");
    messageBox.setInformativeText("Try again?");
    messageBox.setIconPixmap(QPixmap(":/images/bomb_explode").scaled(64, 64, Qt::KeepAspectRatio));
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::Yes);
    int ret = messageBox.exec(); // Display the message box
    if (ret == QMessageBox::Yes)
        resetGame(); // Reset the game if the user wants to play again
    else if (ret == QMessageBox::No)
        QCoreApplication::exit(0); // Exit the application
}