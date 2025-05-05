#ifndef TILES_H
#define TILES_H

#include <QGraphicsRectItem>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QString>
#include <QFont>

// ============================================================================
// Class: Tiles, ColorTiles, ProgressTile
// Overview:
//   This class defines behavior in regards to visual components of
//   several types of tiles all extending from base class Tile
// ============================================================================


class Tile : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // Constructor to set tiles as selectable
    Tile(int size, QGraphicsItem* parent = nullptr) : QObject(), QGraphicsRectItem(0, 0, size, size, parent), color(Qt::lightGray) {
        setFlag(QGraphicsItem::ItemIsSelectable);
    }
    // Getters and setters
    QColor getColor() { return color; }
    void setColor(QColor color) { this->color = color; }

protected:
    QColor color; // Color of tile
    // paint() method to draw color of tile
    void paint(QPainter* p, const QStyleOptionGraphicsItem* o, QWidget* w) override {
        p->setBrush(color);
        p->setPen(Qt::NoPen);
        p->drawRect(rect());
    }
};


class ColorTile : public Tile {
    Q_OBJECT
public:
    // Constructor to set some variables
    ColorTile(int size, QGraphicsItem* parent = nullptr) : Tile(size, parent), number(0), _showNumber(false) {}

    void setNumber(int n)    { number = n; update(); } // sets number that will be drawn over
    void showNumber(bool on) { _showNumber = on; update(); } // show the number to draw over

    // Getters and setters for tile location
    void setGridPosition(int r, int c) { row = r; col = c; }
    int getRow() const { return row; }
    int getCol() const { return col; }

    // Draw and remove X over the tile with respective color from player
    void unmarkX() { marked = false; }
    void markX(const QColor& xColor) {
        marked = true;
        markColor = xColor;
        update();
    }
signals:
    void clicked(ColorTile* tile); // signal to send when a tile has been clicked (handleTileClicked () )

protected:
    int  number; // Current number
    bool _showNumber; // Showing the number

    // Override paint method to extend it with simple logic components to draw a number over it or an X or both
    void paint(QPainter* p, const QStyleOptionGraphicsItem* o, QWidget* w) override {
        Tile::paint(p, o, w);

        if (_showNumber && number > 0) {
            p->setPen(Qt::white);
            p->setFont(QFont("Palatino Linotype", 12, QFont::Bold));
            p->drawText(rect(), Qt::AlignCenter, QString::number(number));
        }

        if (marked) {
            p->setPen(QPen(markColor, 3)); // thick colored X
            p->drawLine(rect().topLeft(), rect().bottomRight());
            p->drawLine(rect().topRight(), rect().bottomLeft());
        }
    }
    // Use clicked(ColorTile* tile) signal when tile has been clicked on
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        emit clicked(this);
        Tile::mousePressEvent(event);
    }
private:
    bool marked = false; // X if or if not marked
    QColor markColor = Qt::white; // X color
    // Tile location
    int row;
    int col;
};




class ProgressTile : public Tile {
public:
    // Constructor to set some variables
    ProgressTile(int size, QGraphicsItem* parent = nullptr) : Tile(size, parent), hasPeg(false), pegColor(QColor()) {}

    bool hasPegPlaced() { return hasPeg; } // Return if peg on tile
    void setPegPlaced(bool pegPlaced) { hasPeg = pegPlaced; } // Set if peg on tile


protected:
    bool hasPeg; // Is player on tile
    QColor pegColor; // color of player
};




#endif // TILES_H
