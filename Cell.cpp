// Author: Hirbod Hosseini (251234419) 
// Description of file contents: Main implementation of Cell object
// Date: Feb 2nd, 2024

#include "Cell.h"

// Cell inherits QPushButton constructor

// Constructor has nothing to do
Cell::Cell(QWidget *parent)
    : QPushButton(parent) {
}

// Deconstructor also has nothing to do
Cell::~Cell() {
    // Release any resources or perform cleanup tasks specific to Cell objects
}

/**
 * Function Name: setCoordinates
 * Description: Sets the row and column coordinates of the cell.
 *
 * Parameters:
 *    row (int) - The row number to set for the cell.
 *    col (int) - The column number to set for the cell.
 *
 * Return:
 *    void
 */
void Cell::setCoordinates(int row, int col) {
    this->row = row;
    this->col = col;
}

/**
 * Function Name: getRow
 * Description: <Brief description of what the function does.>
 *
 * Parameters:
 *    (none)
 *
 * Return:
 *    <Type> - <Description of the return value>
 */

int Cell::getRow() const {
    return row;
}

/**
 * Function Name: getCol
 * Description: <Brief description of what the function does.>
 *
 * Parameters:
 *    (none)
 *
 * Return:
 *    <Type> - <Description of the return value>
 */

int Cell::getCol() const {
    return col;
}

/**
 * Function Name: mousePressEvent
 * Description: Handles mouse press events on the cell, specifically to detect right-clicks and emit a signal or defer to the default QPushButton behavior for other types of clicks.
 *
 * Parameters:
 *    event (QMouseEvent*) - The event object that contains details about the mouse press event, including which button was pressed.
 *
 * Return:
 *    void - This function does not return a value.
 */

void Cell::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        emit rightClicked(); // Emits rightClicked signal on right click
    } else {
        QPushButton::mousePressEvent(event); // Default behavior for other clicks
    }
}