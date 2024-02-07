# Author: Hirbod Hosseini (251234419) 
# Description of file contents: .pro file needed for qmake
# Date: Feb 2nd, 2024


# Add core, gui, and widgets modules from the Qt framework to the project.
QT += core gui widgets

# Specify the C++ standard to use, in this case, C++11.
# This enables features of the C++11 standard and ensures compatibility.
CONFIG += c++11

# The name of the target binary that will be produced (Minesweeper in this case).
TARGET = Minesweeper

# List of source files used in the project.
# main.cpp is the entry point of the application, and Minesweeper.cpp contains
# the implementation of the Minesweeper game logic and UI.
SOURCES += main.cpp \
           Minesweeper.cpp \
           Cell.cpp

# List of header files used in the project.
# Minesweeper.h is the header for the Minesweeper game's main class.
HEADERS += Minesweeper.h \
           Cell.h

# List of resource files (.qrc) which include assets like images and icons
# used within the application. Resources are compiled into the application binary.
# I had to do this because for some reason local paths wouldn't work. I know there is a much easier way I just couldn't get it running that way
RESOURCES += resources.qrc

# Placeholder for UI form files (if using Qt Designer for UI layout).
# Uncomment and list your .ui files here if your project includes any.
# FORMS +=

# Placeholder for linking additional libraries.
# Uncomment and specify any external libraries your project needs.
# LIBS +=

# Placeholder for additional platform-specific configurations.
# You can specify different configurations for different target platforms here.
# For example, specific compiler flags or platform-specific libraries.
# CONFIG += ...
