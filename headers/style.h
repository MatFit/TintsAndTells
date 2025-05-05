#ifndef STYLE_H
#define STYLE_H
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QLCDNumber>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QGroupBox>
#include <QGraphicsScene>
#include <QTextEdit>
#include "tiles.h"


// ============================================================================
// Class: Style
// Pattern: Singleton
// Overview:
//   This class handles visual changes for all QWidgets
//   including QMainWindow
// ============================================================================


class Style
{
public:
    static Style* getInstance() {
        if (!instance) instance = new Style();
        return instance;
    }

    void styleTitleAndMain(QLabel* title, QMainWindow* game); // Background and Title

    // Color and progress board design
    QVector<QVector<ColorTile*>> styleBoards(int rows, int cols, QGraphicsView* colorView, QMainWindow* game);
    QVector<QVector<ProgressTile*>> styleProgressBoard(int numPlayers, int totalPoints, QGraphicsView* progressView, QMainWindow* game);

    void styleProgressTiles(QPushButton* progressTile); // Progress Tiles
    void styleColorTiles(QPushButton* colorTile); // Color Tiles
    void styleMenu(QGroupBox* menu); // Menu
    void styleLabel(QLabel* label);
    void styleQGiverNotificationLabel(QLabel* box, QString giver_name); // QGiver labels
    void styleQGiverNotificationRecieveLabel(QLabel* label); // QGiver first UI notification
    void styleQGiverNotificationRecieveTextBox(QTextEdit* box); // QGiver second UI notification when recieveing the color
    void styleNotificationTextEdit(QTextEdit* textEdit); // Style text boxes
    void stylePushButtons(QPushButton* button); // Buttons
    void styleTimer(QLCDNumber *timer); // Timer

    void createPalette(int ROW, int COL); // creates a 2d vector of a pallete of colors for the tiles
    QColor getPaletteColor(int row, int col) const {return palette[row][col]; } // Returns a certain color from the pallete

private:
    static Style* instance; // Single instance of style class
    QVector<QVector<QColor>> palette; // Pallete vector
    Style(); // base constructor
};

#endif // STYLE_H
