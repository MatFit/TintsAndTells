#include "game.h"
#include "tiles.h"
#include "qgivernotification.h"
#include "PlayerFactory.h"
#include "ui_game.h"


/*
Possible TODOs:
    Restart option
    Randomized abilities
    Larger spectrum
*/


// -----------------------------------------------------------------------------
// ~Game()
// Destructor to delete the entirety of the game object when finished
// -----------------------------------------------------------------------------
Game::~Game()
{
    delete ui;
}

// -----------------------------------------------------------------------------
// Game()
// Constructor that will call the necessary and base methods
// -----------------------------------------------------------------------------
Game::Game(QWidget *parent) : QMainWindow(parent), ui(new Ui::Game)
{
    ui->setupUi(this);

    // Fetching ui elements
    colorBoard = ui->colorBoard;
    progressBoard = ui->progressBoard;

    // Fetching just singular instance of style class
    style = Style::getInstance();

    // Big method
    initializeGame();
}

// -----------------------------------------------------------------------------
// fetchPlayers()
// This method will intiialize the game components using sub methods and
// objects like ability stratigies a
// -----------------------------------------------------------------------------
void Game::initializeGame() {
    fetchPlayers();
    styleGame();
    connecting();
    setupInitialProgressPegs();


    // Set up abilities here for ui->ability_1 - 3
    strategy_1 = new DoublePointsStrategy();
    strategy_2 = new TriplePointsStrategy();
    strategy_3 = new NullifyOpponentPointsStrategy();

    ui->ability_1->setText(QString::fromStdString(strategy_1->getName()));
    ui->ability_2->setText(QString::fromStdString(strategy_2->getName()));
    ui->ability_3->setText(QString::fromStdString(strategy_3->getName()));
}

// -----------------------------------------------------------------------------
// fetchPlayers()
// Prior to the actual game we use this to fetch players name
// -----------------------------------------------------------------------------
void Game::fetchPlayers(){
    bool success;

    while (true) {
        QString giver_name = QInputDialog::getText(this, tr("Giver Name"), tr("Enter Q Giver Name:"), QLineEdit::Normal, QString(), &success);
        if (success && !giver_name.isEmpty()) {
            giver = static_cast<QGiver*>(PlayerFactory::createPlayer(PlayerType::QGiver, giver_name)); // i hate forced designed patterns
            break;
        }
        if (!success) {
            QTimer::singleShot(0, this, SLOT(close()));
            return;
        }
    }

    while (true) {
        QString player_1_name = QInputDialog::getText(this, tr("Player 1 Name"), tr("Enter Player 1 Name:"), QLineEdit::Normal, QString(), &success);
        if (success && !player_1_name.isEmpty()) {
            player_1 = static_cast<Guesser*>(PlayerFactory::createPlayer(PlayerType::Guesser, player_1_name, Qt::red)); // i hate forced designed patterns
            break;
        }
        if (!success) {
            QTimer::singleShot(0, this, SLOT(close()));
            return;
        }
    }

    while (true) {
        QString player_2_name = QInputDialog::getText(this, tr("Player 2 Name"), tr("Enter Player 2 Name:"), QLineEdit::Normal, QString(), &success);
        if (success && !player_2_name.isEmpty()) {
            player_2 = static_cast<Guesser*>(PlayerFactory::createPlayer(PlayerType::Guesser, player_2_name, Qt::blue)); // i hate forced designed patterns
            break;
        }
        if (!success) {
            QTimer::singleShot(0, this, SLOT(close()));
            return;
        }
    }


}

// -----------------------------------------------------------------------------
// connecting()
// This method connects game assets to respective slots defined below
// -----------------------------------------------------------------------------
void Game::connecting() {
    connect(ui->startGame, &QPushButton::clicked,this, &Game::onStartGame);
    connect(ui->ability_1, &QPushButton::clicked,this, &Game::handleAbilityClicked);
    connect(ui->ability_2, &QPushButton::clicked,this, &Game::handleAbilityClicked);
    connect(ui->ability_3, &QPushButton::clicked,this, &Game::handleAbilityClicked);

    for (const auto& row : tiles) {
        for (ColorTile* tile : row) {
            connect(tile, &ColorTile::clicked, this, &Game::handleTileClicked);
        }
    }

    connect(ui->forfeit, &QPushButton::clicked,this, &Game::handleForfeit);
}


// -----------------------------------------------------------------------------
// styleGame()
// Houses the bulk use of the Style class to redesign the game when booted up
// -----------------------------------------------------------------------------
void Game::styleGame(){
    tiles = style->styleBoards(ROW, COL, ui->colorBoard, this);
    progressTiles = style->styleProgressBoard(NUM_PLAYERS, TOTAL_POINTS, ui->progressBoard, this);

    style->styleTitleAndMain(ui->title, this);
    style->styleMenu(ui->menu);
}



// -----------------------------------------------------------------------------
// onStartGame()
// Check to see two states, when start game is clicked we give the Q-Giver
// their color, otherwise we can begin the actual game
// -----------------------------------------------------------------------------
void Game::onStartGame() {
    if (!gameStart){
        qDebug() << "Game started";
        // give QGiver random location from
        int randRow = QRandomGenerator::global()->bounded(ROW);
        int randCol = QRandomGenerator::global()->bounded(COL);

        // Get the color at that random location
        QColor randomColor = style->getPaletteColor(randRow, randCol);

        giver->setTrueColor(randomColor);
        giver->setLocationofTrueColor(randRow, randCol);

        // Throw Q Giver notification
        QGiverNotification *notif = new QGiverNotification(this, giver);
        notif->setWindowModality(Qt::ApplicationModal); // focus on notification window
        notif->show();    // non-blocking


        ui->startGame->setText("Begin");
        gameStart = true;
    }
    else{
        // Actually beginning the game, at this point q giver has given their desc to guessers
        // Now we have two players player_1, player_2
        resetBoard();

        playerTurn = true; // now the color board accepts clicks
        currentPlayer = player_1; // track whose turn it is
        ui->startGame->setText(player_1->getName() + "'s Turn!");
        ui->startGame->setEnabled(false); // Disable start button now

        // Start timer
        countdownTimer = new QTimer(this);
        remainingTime = 30; // 20 seconds
        ui->timer->display(remainingTime);
        connect(countdownTimer, &QTimer::timeout, this, &Game::updateCountdown);
        countdownTimer->start(1000);

        gameBegin = true;
    }
}

// -----------------------------------------------------------------------------
// setupInitialProgressPegs()
// Draw pegs on the progress board along with assigning those pegs to
// the respective players
// -----------------------------------------------------------------------------
void Game::setupInitialProgressPegs() {
    if (!pegsMade) {
        QGraphicsScene* progScene = progressBoard->scene();

        if (!progScene) {
            progScene = new QGraphicsScene(this);
            progressBoard->setScene(progScene);
        }

        int pegSize = tileSize / 2;
        int offset = (tileSize - pegSize) / 2;

        // Player 1
        QGraphicsEllipseItem* peg1 = progScene->addEllipse(
            offset, offset,
            pegSize, pegSize,
            QPen(Qt::black),
            QBrush(player_1->getColor())
            );
        player_1->setPeg(peg1);
        player_1->setPegX(0);
        player_1->setPegY(0);

        qDebug() << "asduinasd" << player_1->getPegX() << "   ,    " << player_1->getPegY();


        // Player 2
        QGraphicsEllipseItem* peg2 = progScene->addEllipse(
            offset, tileSize + spacing + offset,
            pegSize, pegSize,
            QPen(Qt::black),
            QBrush(player_2->getColor())
            );
        player_2->setPeg(peg2);
        player_2->setPegX(0);
        player_2->setPegY(1);

        pegsMade = true;
    }

}

// -----------------------------------------------------------------------------
// movePegForward()
// After a round has been evaluted, this method controls the animation
// display of player pegs on the progress board to move reflecting
// players points
// -----------------------------------------------------------------------------
void Game::movePegForward(QGraphicsEllipseItem* peg, int points) {
    const int movePerTile = tileSize + spacing;
    int totalMove = points * movePerTile;
    int interval = 25;
    int stepDistance = totalMove / 20;
    int* moved = new int(0);

    int maxX = (TOTAL_POINTS - 1) * movePerTile; // Progress board size, cap how far the peg moves

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        QPointF pos = peg->pos();

        // Check if peg goes beyond board
        if (pos.x() >= maxX) {
            peg->setPos(maxX, pos.y()); // Snap to end and return
            timer->stop();
            timer->deleteLater();
            delete moved;
            return;
        }


        if (*moved >= totalMove) {
            QPointF pos = peg->pos();
            qreal finalX = pos.x() + (totalMove - *moved); // grab destination x
            if (finalX > maxX) finalX = maxX; // Cap finalX
            peg->setPos(finalX, pos.y());

            timer->stop();
            timer->deleteLater();
            delete moved;
            return;
        }

        // While moved is less than total moved
        peg->moveBy(stepDistance, 0);
        *moved += stepDistance;
    });

    timer->start(interval);
}

// -----------------------------------------------------------------------------
// handleTileClicked()
// When a tile is clicked, this method handles to see who has clicked it
// and paint visuals when clicked
// -----------------------------------------------------------------------------
void Game::handleTileClicked(ColorTile* clickedTile) {
    if (!gameBegin || !playerTurn) return;

    countdownTimer->stop(); // Stop timer

    clickedTile->markX(currentPlayer->getColor()); // Paint X over tile

    currentPlayer->setChosenTile(clickedTile); // Set chosen tile to player

    // Switch turns if player_1 else check end of round
    if (currentPlayer == player_1) {
        // player 2’s turn
        currentPlayer = player_2;
        playerTurn    = true;
        ui->startGame->setText(currentPlayer->getName() + "'s Turn!");
        // restart countdown for player 2
        remainingTime = 30;
        ui->timer->display(remainingTime);
        countdownTimer->start(1000);
    }
    else {
        // both have chosen → compare their chosenTile->getColor() to giver->getTrueColor()
        evaluateRound();
    }
}

// -----------------------------------------------------------------------------
// evaluateRound()
// After both players have made their choice, evalute the final result of the
// round by checking points, abilities, and game state
// -----------------------------------------------------------------------------
void Game::evaluateRound() {
    if (!player_1 || !player_2) return;

    int trueRow = giver->getLocationofTrueColorX();
    int trueCol = giver->getLocationofTrueColorY();

    ColorTile* trueTile = tiles[trueRow][trueCol];


    ColorTile* tile1 = player_1->getChosenTile();
    ColorTile* tile2 = player_2->getChosenTile();

    // Calculate points based off of tiles
    int points1 = calculatePoints(tile1, trueTile);
    int points2 = calculatePoints(tile2, trueTile);



    // Use Abilities
    if (player_1->getActiveAbility() == 1 ){ points1 = strategy_1->modifyPoints(points1); }
    else if (player_1->getActiveAbility() == 2 ){ points1 = strategy_2->modifyPoints(points1); }

    if (player_2->getActiveAbility() == 1 ){ points2 = strategy_1->modifyPoints(points2); }
    else if (player_2->getActiveAbility() == 2 ){ points2 = strategy_2->modifyPoints(points2); }

    if (player_1->getActiveAbility() == 3) { points2 = strategy_3->returnToZero(); }
    else if (player_2->getActiveAbility() == 3) { points1 = strategy_3->returnToZero(); }


    // Reset player active abilites
    player_1->setActiveAbility(-1);
    player_2->setActiveAbility(-1);


    // Set peg location
    player_1->setPegY(player_1->getPegY() + points1);
    player_2->setPegY(player_2->getPegY() + points2);

    // Move pegs
    if (points1 > 0) movePegForward(player_1->getPeg(), points1);
    if (points2 > 0) movePegForward(player_2->getPeg(), points2);


    // Draw 3 on true tile
    trueTile->setNumber(3);
    trueTile->showNumber(true);

    // Draw 1 on surround tiles
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;

            int r = trueRow + dr;
            int c = trueCol + dc;

            if (r >= 0 && r < ROW && c >= 0 && c < COL) {
                ColorTile* neighbor = tiles[r][c];
                if (neighbor) {
                    neighbor->setNumber(1);
                    neighbor->showNumber(true);
                }
            }
        }
    }


    // Check if game OVER
    if (isGameOver()) {
        QString winnerName = "Both";

        if (player_1->getPegY() >= TOTAL_POINTS - 1) {
            winnerName = player_1->getName();
        }
        else if (player_2->getPegY() >= TOTAL_POINTS - 1) {
            winnerName = player_2->getName();
        }
        else {
            winnerName = "Everyone!";
        }

        QMessageBox* gameOverBox = new QMessageBox();
        gameOverBox->setText("Game Over! Winner: " + winnerName);

        QPushButton* closeButton = gameOverBox->addButton("Close", QMessageBox::AcceptRole);
        connect(closeButton, &QAbstractButton::released, this, &Game::close);

        gameOverBox->exec();
    }


    // Disable player clicking
    playerTurn = false;

    // Set for next round
    ui->startGame->setEnabled(true);
    ui->startGame->setText("Next Round");
    gameStart = false;
}



// -----------------------------------------------------------------------------
// updateCountdown()
// Iterate the time and handle player switching it timeout for some player turn
// -----------------------------------------------------------------------------
void Game::updateCountdown() {
    // When 0, switch players if player 1 or check end Round state
    if (--remainingTime <= 0) {
        countdownTimer->stop();
        qDebug() << "Time's up for" << currentPlayer->getName();

        // Switch turn as if they missed their guess
        if (currentPlayer == player_1) {
            currentPlayer = player_2;
            playerTurn = true;

            ui->startGame->setText(currentPlayer->getName() + "'s Turn!");
            ui->startGame->setEnabled(false);

            remainingTime = 30;
            ui->timer->display(remainingTime);
            countdownTimer->start(1000);
        }
        else {
            playerTurn = false;
            evaluateRound();
        }
    }
    else {
        ui->timer->display(remainingTime);
    }
}

// -----------------------------------------------------------------------------
// calculatePoints()
// Calculates points recieved of players with their chosen tile, how close they
// were the the right tile
// -----------------------------------------------------------------------------
int Game::calculatePoints(ColorTile* choice, ColorTile* trueTile) {
    if (!choice || !trueTile) return 0;

    // Find points based on if on true tile or around it
    int xChoice = choice->getRow();
    int yChoice = choice->getCol();
    int xTrue   = trueTile->getRow();
    int yTrue   = trueTile->getCol();

    if (xChoice == xTrue && yChoice == yTrue) {
        return 3; // One and done
    }
    else if (abs(xChoice - xTrue) <= 1 && abs(yChoice - yTrue) <= 1) {
        return 1; // adjacent
    }
    else {
        return 0;
    }
}

// -----------------------------------------------------------------------------
// resetBoard()
// Reset board by cleaning what has been drawn
// -----------------------------------------------------------------------------
void Game::resetBoard() {
    for (auto& row : tiles) {
        for (ColorTile* tile : row) {
            if (!tile) continue;

            tile->setNumber(0);        // clear number
            tile->showNumber(false);   // Hide number
            tile->unmarkX();           // Clear X
            tile->update();
        }
    }
}

// -----------------------------------------------------------------------------
// isGameOver()
// Checks peg location if at the end
// -----------------------------------------------------------------------------
bool Game::isGameOver() {
    int lastTileIndex = TOTAL_POINTS - 1;

    if (player_1->getPegY() >= lastTileIndex) {
        return true;
    }

    if (player_2->getPegY() >= lastTileIndex) {
        return true;
    }

    return false;
}


// -----------------------------------------------------------------------------
// handleAbilityClicked()
// When an ability it clicked toggle active ability for current player who clicked it
// -----------------------------------------------------------------------------
void Game::handleAbilityClicked(){
    if (!gameStart) { return; }
    if (!currentPlayer) { return; }

    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (!senderButton) return;

    if (senderButton == ui->ability_1 && currentPlayer->getAbility1()) {
        currentPlayer->setActiveAbility(1);
        currentPlayer->setAbility1(false);
    }
    else if (senderButton == ui->ability_2 && currentPlayer->getAbility2()) {
        currentPlayer->setActiveAbility(2);
        currentPlayer->setAbility1(false);
    }
    else if (senderButton == ui->ability_3 && currentPlayer->getAbility3()) {
        currentPlayer->setActiveAbility(3);
        currentPlayer->setAbility1(false);
    }
}


// -----------------------------------------------------------------------------
// handleForfeit()
// Called when the current player forfeits.
// -----------------------------------------------------------------------------
void Game::handleForfeit(){

    QString winnerName = "Neither";

    // Check for winner name
    if (currentPlayer == player_1) {
        winnerName = player_2->getName();
    }
    else if (currentPlayer == player_2) {
        winnerName = player_1->getName();
    }
    // Output message box declaring the winner
    QMessageBox* gameOverBox = new QMessageBox();
    gameOverBox->setText("Game Over! Winner: " + winnerName);

    QPushButton* closeButton = gameOverBox->addButton("Close", QMessageBox::AcceptRole);
    connect(closeButton, &QAbstractButton::released, this, &Game::close);

    gameOverBox->exec();
}
