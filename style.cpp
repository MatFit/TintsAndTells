#include "style.h"
#include "tilefactory.h"

Style* Style::instance = nullptr; // For Singleton pattern

Style::Style() {} // Generic constructor

// -----------------------------------------------------------------------------
// styleTitleAndMain()
// Method to style title and main window
// -----------------------------------------------------------------------------
void Style::styleTitleAndMain(QLabel* title, QMainWindow* game) {
    // Style background
    game->setStyleSheet("background-color: black;");

    // Config and style title
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "color: white;"
        "font-size: 48px;"
        "font-family: 'Century Gothic', 'Trebuchet MS', sans-serif;"
        "font-weight: bold;"
        );
}

// -----------------------------------------------------------------------------
// stylePushButtons()
// Method to style push buttons
// -----------------------------------------------------------------------------
void Style::stylePushButtons(QPushButton *button) {
    // Config button
    button->setCursor(Qt::PointingHandCursor);

    // Style button
    button->setStyleSheet(
        "QPushButton {"
        "  background-color: #444;"
        "  color: white;"
        "  border: 2px solid #666;"
        "  border-radius: 8px;"
        "  padding: 6px 12px;"
        "  font-family: 'Trebuchet MS', sans-serif;"
        "  font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #555;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #333;"
        "}"
        );
}

// -----------------------------------------------------------------------------
// styleLabel()
// Method to style QLabels
// -----------------------------------------------------------------------------
void Style::styleLabel(QLabel *label) {
    // Config label
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);
    // Style label
    label->setStyleSheet(R"(
        background-color: transparent;
        color: #F0F0F0;
        font-family: 'Palatino Linotype', 'Georgia', serif;
        font-size: 25px;
        font-style: italic;
        font-weight: bold;
        border-bottom: 2px solid #F0F0F0; /* underline */
    )");
}

// -----------------------------------------------------------------------------
// styleTimer()
// Method to style timer
// -----------------------------------------------------------------------------
void Style::styleTimer(QLCDNumber *timer) {
    // Config timer
    timer->setSegmentStyle(QLCDNumber::Flat);
    timer->setDigitCount(2);
    timer->setSmallDecimalPoint(true);
    // Style the timer
    timer->setStyleSheet(
        "QLCDNumber {"
        "  background-color: #111;"
        "  border: 2px solid #808080;"
        "  border-radius: 4px;"
        "  color: #00FF00;"
        "}"
        );
}
// -----------------------------------------------------------------------------
// styleTimer()
// Method to style menu (QGroupBox)
// -----------------------------------------------------------------------------
void Style::styleMenu(QGroupBox* menu) {
    // Styling the menu
    menu->setStyleSheet(
        "QGroupBox {"
        "  background-color: #333;"
        "  border: 2px solid #555;"
        "  border-radius: 10px;"
        "  margin-top: 1.2em;"
        "  padding: 8px;"
        "}"
        "QGroupBox::title {"
        "  subcontrol-origin: margin;"
        "  subcontrol-position: top center;"
        "  color: white;"
        "  font-family: 'Century Gothic', sans-serif;"
        "  font-size: 18px;"
        "  font-weight: bold;"
        "}"
        );

    // Iterate through all child widgets
    for (auto w : menu->findChildren<QWidget*>()) {
        // If data type QLabal, style label
        if (auto lbl = qobject_cast<QLabel*>(w)) {
            styleLabel(lbl);
        }
        // If data type QPushButton, style button
        else if (auto btn = qobject_cast<QPushButton*>(w)) {
            stylePushButtons(btn);
        }
        // If data type QLCDNumber, style timer
        else if (auto lcd = qobject_cast<QLCDNumber*>(w)) {
            styleTimer(lcd);
        }
    }
}

// -----------------------------------------------------------------------------
// styleQGiverNotificationLabel(QLabel* box, QString giver_name)
// Method to style first UI notification's labels for QGiver
// -----------------------------------------------------------------------------
void Style::styleQGiverNotificationLabel(QLabel* box, QString giver_name) {
    box->setAlignment(Qt::AlignCenter);
    box->setText("ONLY " + giver_name.toUpper() + " CAN SEE THE SCREEN");

    // fancier, bolder styling
    box->setStyleSheet(R"(
        QLabel {
            background-color: #555;
            color: white;
            border: 2px solid #BBB;
            border-radius: 8px;
            padding: 6px 12px;
            font-family: 'Palatino Linotype', 'Georgia', serif;
            font-size: 14px;
            font-weight: bold;
            letter-spacing: 1px;            /* slight spacing between letters */
            text-transform: uppercase;      /* all-caps */
        }
    )");
}

// -----------------------------------------------------------------------------
// styleQGiverNotificationRecieveLabel(QLabel* box)
// Method to style second UI notification's labels
// -----------------------------------------------------------------------------
void Style::styleQGiverNotificationRecieveLabel(QLabel* box) {
    box->setAlignment(Qt::AlignCenter);

    // fancier, bolder styling
    box->setStyleSheet(R"(
        QLabel {
            background-color: #555;
            color: white;
            border: 2px solid #BBB;
            border-radius: 8px;
            padding: 6px 12px;
            font-family: 'Palatino Linotype', 'Georgia', serif;
            font-size: 12px;
            font-weight: bold;
            letter-spacing: 1px;            /* slight spacing between letters */
            text-transform: uppercase;      /* all-caps */
        }
    )");
}

// -----------------------------------------------------------------------------
// styleQGiverNotificationRecieveTextBox(QTextEdit* box)
// Method to style second UI notification's text box
// -----------------------------------------------------------------------------
void Style::styleQGiverNotificationRecieveTextBox(QTextEdit* box) {
    box->setAlignment(Qt::AlignCenter);

    box->setStyleSheet(R"(
        QTextEdit {
            background-color: #555;
            color: white;
            border: 2px solid #BBB;
            border-radius: 8px;
            padding: 6px 12px;
            font-family: 'Palatino Linotype', 'Georgia', serif;
            font-size: 14px;
            font-weight: bold;
            letter-spacing: 1px;
            text-transform: uppercase;
        }
    )");
}

// -----------------------------------------------------------------------------
// styleNotificationTextEdit(QTextEdit* edit)
// Method to style notification's text box
// -----------------------------------------------------------------------------
void Style::styleNotificationTextEdit(QTextEdit* edit) {
    edit->setStyleSheet(R"(
        QTextEdit {
            background-color: #666;
            color: white;
            border: 2px solid #BBB;
            border-radius: 8px;
            padding: 4px 8px;
        }
        QTextEdit:focus {
            border-color: #888;
        }
    )");

    QTextOption opt = edit->document()->defaultTextOption();
    opt.setAlignment(Qt::AlignCenter);
    edit->document()->setDefaultTextOption(opt);

    // Change font
    QTextCursor cursor(edit->document());
    cursor.select(QTextCursor::Document);
    QTextCharFormat cf;
    cf.setFont(QFont("Century Gothic", 12));
    cursor.mergeCharFormat(cf);

    edit->setCurrentCharFormat(cf);
}

// -----------------------------------------------------------------------------
// styleNotificationTextEdit(QTextEdit* edit)
// This method creates palletes that is used to create the spectrum of colors,
// it iterates through the 2D board and adjust brightness, hue, and
// saturation each time to give a spectrum of that
// -----------------------------------------------------------------------------
void Style::createPalette(int rows, int cols) {
    // Clear and resize the palette
    palette.resize(rows);

    for (int r = 0; r < rows; ++r) {
        palette[r].resize(cols);

        int brightness = 255 - (r * 155 / (rows - 1));
        int saturation = 255;

        for (int c = 0; c < cols; ++c) {
            int hue = (c * 360) / (cols + 2);

            // Create color
            palette[r][c] = QColor::fromHsv(hue, saturation, brightness);
        }
    }
}
// -----------------------------------------------------------------------------
// QVector<QVector<ColorTile*>> Style::styleBoards(int rows,
// int cols, QGraphicsView* colorView, QMainWindow* game)
//
// Method to styles color board from main window and returns a 2D vector of
// the tiles for later usage in logic sections
// -----------------------------------------------------------------------------
QVector<QVector<ColorTile*>> Style::styleBoards(int rows, int cols, QGraphicsView* colorView, QMainWindow* game)
{
    // Pointer returned for later use
    QVector<QVector<ColorTile*>> createdTiles;
    createdTiles.resize(rows);

    // Create palette
    createPalette(rows, cols);

    // Set graphic scenes
    QGraphicsScene* colorScene = new QGraphicsScene(game);
    colorView->setScene(colorScene);

    // Set dimensions
    const int tileSize   = 43;
    const int spacing    = 4;
    const int labelMargin = 20;

    // Add color tiles
    for (int r = 0; r < rows; ++r) {
        createdTiles[r].resize(cols); // Resize row
        for (int c = 0; c < cols; ++c) {
            // Idk man gives me an excuse to use factory
            Tile* baseTile = TileFactory::createTile(TileType::Color, tileSize);
            auto* tile = static_cast<ColorTile*>(baseTile);

            tile->setGridPosition(r, c);
            createdTiles[r][c] = tile; // store properly in 2D to return

            tile->setColor(palette[r][c]);
            tile->showNumber(false);
            colorScene->addItem(tile);
            tile->setPos(
                c * (tileSize + spacing),
                r * (tileSize + spacing)
                );
        }
    }


    // Add column labels (1, 2, 3…) on top
    for (int c = 0; c < cols; ++c) {
        QGraphicsTextItem* lbl = colorScene->addText(QString::number(c + 1));
        lbl->setDefaultTextColor(Qt::white);
        lbl->setFont(QFont("Century Gothic", 10, QFont::Bold));


        double x = c * (tileSize + spacing) + (tileSize + spacing) / 2 - lbl->boundingRect().width() / 2;


        lbl->setPos(x, -labelMargin);
    }

    // Add row labels (A, B, C…) left hand
    for (int r = 0; r < rows; ++r) {
        QGraphicsTextItem* lbl = colorScene->addText(QString(QChar('A' + r)));
        lbl->setDefaultTextColor(Qt::white);
        lbl->setFont(QFont("Century Gothic", 10, QFont::Bold));


        double y = r * (tileSize + spacing) + (tileSize + spacing) / 2 - lbl->boundingRect().height() / 2;


        lbl->setPos(-labelMargin, y);
    }

    // Add column labels (1, 2, 3…) on top
    for (int c = 0; c < cols; ++c) {
        QGraphicsTextItem* lbl = colorScene->addText(QString::number(c + 1));
        lbl->setDefaultTextColor(Qt::white);
        lbl->setFont(QFont("Century Gothic", 10, QFont::Bold));


        double x = c * (tileSize + spacing) + (tileSize + spacing) / 2 - lbl->boundingRect().width() / 2;
        double y = rows * (tileSize + spacing); // bottom side, after last row


        lbl->setPos(x, y + spacing); // small extra spacing
    }

    // Add row labels (A, B, C…) right hand
    for (int r = 0; r < rows; ++r) {
        QGraphicsTextItem* lbl = colorScene->addText(QString(QChar('A' + r)));
        lbl->setDefaultTextColor(Qt::white);
        lbl->setFont(QFont("Century Gothic", 10, QFont::Bold));
        double x = cols * (tileSize + spacing); // right side, after last column
        double y = r * (tileSize + spacing) + (tileSize + spacing) / 2 - lbl->boundingRect().height() / 2;
        lbl->setPos(x + spacing, y); // small extra spacing
    }


    return createdTiles;
}

// -----------------------------------------------------------------------------
// QVector<QVector<ProgressTile*>> Style::styleProgressBoard(int numPlayers,
// int totalPoints, QGraphicsView* progressView, QMainWindow* game)
//
// Method to styles progress board from main window and returns a 2D vector of
// the tiles for later usage in logic sections
// -----------------------------------------------------------------------------
QVector<QVector<ProgressTile*>> Style::styleProgressBoard(int numPlayers, int totalPoints, QGraphicsView* progressView, QMainWindow* game) {
    const int tileSize = 43;
    const int spacing  = 4;

    QVector<QVector<ProgressTile*>> createdTiles;
    createdTiles.resize(numPlayers);

    QGraphicsScene* progScene = new QGraphicsScene(game);
    progressView->setScene(progScene);

    for (int player = 0; player < numPlayers; ++player) {
        createdTiles[player].resize(totalPoints);

        for (int i = 0; i < totalPoints; ++i) {
            Tile* basePt = TileFactory::createTile(TileType::Progress, tileSize);
            auto* pt = static_cast<ProgressTile*>(basePt);

            createdTiles[player][i] = pt;

            pt->setColor(Qt::darkGray);
            progScene->addItem(pt);
            pt->setPos(i * (tileSize + spacing), player * (tileSize + spacing));
        }
    }


    // Adjusted dimensions for border
    int borderMargin = 15;
    int boardWidth  = totalPoints * (tileSize + spacing) - spacing;
    int boardHeight = numPlayers * (tileSize + spacing) - spacing;

    // Draw border
    QPen borderPen(Qt::white);
    borderPen.setWidth(4); // pen thickness
    progScene->addRect(
        -borderMargin,                  // shift left
        -borderMargin,                  // shift up
        boardWidth + 2 * borderMargin,   // wider
        boardHeight + 2 * borderMargin,  // taller
        borderPen
    );


    return createdTiles;
}







