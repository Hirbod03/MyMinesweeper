#include "Minesweeper.h" // Include the header file for the Minesweeper game class

int main(int argc, char *argv[]) {
    // Initialize the QApplication object with command-line arguments. 
    // QApplication is required for any application that uses Qt's GUI.
    QApplication app(argc, argv);

    // Create an instance of the MinesweeperGame class.
    // This class manages the game's GUI and logic.
    MinesweeperGame game;

    // Display the game window. The show method is inherited from QWidget 
    // and it makes the window visible on the screen.
    game.show();

    // Enter the main event loop and wait for user interaction.
    // The exec method starts Qt's event handling mechanism. 
    // It returns an exit code when the application is closed.
    return app.exec();
}
