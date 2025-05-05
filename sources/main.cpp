#include "game.h"
#include <QApplication>

// ============================================================================
// Class: Main
// Overview:
//   Main class with main function to run Game class
// ============================================================================

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game w; // Call game object
    w.show(); // Display UI
    return a.exec(); // Exectue
}
