#ifndef GAME_H
#define GAME_H
#include <QTimer>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGroupBox>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QPushButton>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QPropertyAnimation>
#include <QMessageBox>
#include "style.h"
#include "player.h"
#include "TileFactory.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Game;
}
QT_END_NAMESPACE


// ============================================================================
// Class: Game
// Overview:
//   The driver class that handles interaction of multiple components to
//   the game. This ranges from logic, style, and UI context switching
//   (along with anything else)
// ============================================================================


class Game : public QMainWindow
{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    ~Game();
    void initializeGame(); // Create the game
    void styleGame(); // Style the game elements
    void connecting(); // connect elements
    void fetchPlayers(); // grab player names
    void setupInitialProgressPegs(); // set up pegs
    void movePegForward(QGraphicsEllipseItem* peg, int points); // move pegs
    void handleTileClicked(ColorTile* clickedTile); // monitor tiles clicked
    void handleForfeit(); // forfeit method
    void evaluateRound(); // round results
    void resetBoard(); // reset board
    bool isGameOver(); // check game over
    int calculatePoints(ColorTile* choice, ColorTile* trueTile); // figure out points calculated

private slots:
    void onStartGame(); // when starting game
    void handleAbilityClicked(); // when ability clicked
    void updateCountdown(); // updating timer


private:
    // COLOR BOARD SIZE
    const int ROW = 12;
    const int COL = 20;

    // PROGRESS BOARD SIZE
    const int TOTAL_POINTS = 12;
    const int NUM_PLAYERS = 2;

    // Misc
    const int tileSize = 43;
    const int spacing  = 4;
    bool gameStart = false;
    bool gameBegin = false;
    bool playerTurn = false;
    bool pegsMade = false;

    // Timer
    QTimer* countdownTimer = nullptr;
    int remainingTime = 30;

    // UI
    Ui::Game *ui;
    Ui::Game *notification_ui; // For Q-Giver notifcation

    // Styler
    Style *style;

    // Board
    QGraphicsView *colorBoard;
    QGraphicsView *progressBoard;

    // Menu
    QGroupBox *menu;

    // Palette to be used
    QVector<QVector<QColor>> palette;
    QVector<QVector<ColorTile*>> tiles;
    QVector<QVector<ProgressTile*>> progressTiles;

    // Abilities
    AbilityStrategy *strategy_1;
    AbilityStrategy *strategy_2;
    NullifyOpponentPointsStrategy *strategy_3;


    // Players
    QGiver *giver;
    Guesser *player_1;
    Guesser *player_2;
    Guesser *currentPlayer = nullptr;
};
#endif // GAME_H
