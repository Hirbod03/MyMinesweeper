// Author: Hirbod Hosseini (251234419) 
// Description of file contents: Cell header files
// Date: Feb 2nd, 2024

#ifndef CELL_H
#define CELL_H

#include <QMouseEvent>
#include <QPushButton>

class Cell : public QPushButton {
    Q_OBJECT

public:
    Cell(QWidget *parent = nullptr); // Constructor declaration
    ~Cell(); // Destructor declaration
    using QPushButton::QPushButton; 
    void setCoordinates(int row, int col);
    int getRow() const;
    int getCol() const;

signals:
    void rightClicked(); // Signal for right click

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    int row, col;
};

#endif // CELL_H
