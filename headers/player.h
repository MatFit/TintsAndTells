#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
#include <QColor>
#include <QGraphicsEllipseItem>
#include "tiles.h"
#include "abilitystrategy.h"

// ============================================================================
// Class: Player, Q-Giver, Guesser
// Overview:
//   This class defines behavior in regards to logical components of
//   several types of players all extending from base class Player
// ============================================================================


class Player {
public:
    // Base player just takes name with only a getter
    Player(const QString& name) : name(name) {}
    QString getName() { return name; }
protected:
    QString name; // Player name
};

class Guesser : public Player {
public:
    // Constructor setting some variables
    Guesser(const QString& name, const QColor& peg_color) : Player(name), peg_color(peg_color), ability_1(true), ability_2(true), ability_3(true) {}

    // Getters n Setters for abilities, peg location, chosen tile, points, ability strategy
    QColor getColor() { return peg_color; }

    int getPegX() { return peg_x; }
    void setPegX(int x) { peg_x = x; }

    int getPegY() { return peg_y; }
    void setPegY(int y) { peg_y = y; }

    bool getAbility1() const    { return ability_1; }
    void setAbility1(bool on)   { ability_1 = on; }

    bool getAbility2() const    { return ability_2; }
    void setAbility2(bool on)   { ability_2 = on; }

    bool getAbility3() const    { return ability_3; }
    void setAbility3(bool on)   { ability_3 = on; }

    int getActiveAbility() const    { return active_ability; }
    void setActiveAbility(int on)   { active_ability = on; }

    void setChosenTile(ColorTile* tile) { chosenTile = tile; }
    ColorTile* getChosenTile() const { return chosenTile; }

    void setPendingPoints(int points) { pendingPoints = points; }
    int getPendingPoints() const { return pendingPoints; }

    void setAbilityStrategy(AbilityStrategy* strategy) { activeAbility = strategy; }

    QGraphicsEllipseItem* getPeg() const { return peg; }
    void setPeg(QGraphicsEllipseItem* newPeg) { peg = newPeg; }



private:
    QColor peg_color; // Player color peg also used for tile X marks
    QGraphicsEllipseItem* peg; // Player peg
    ColorTile* chosenTile = nullptr; // Player choice of tile

    // Ability variables
    AbilityStrategy* activeAbility;
    int active_ability = -1;
    bool ability_1 = true;
    bool ability_2 = true;
    bool ability_3 = true;

    int pendingPoints = 0; // Player points

    // Player's peg location
    int peg_x;
    int peg_y;
};


class QGiver : public Player {
public:
    QGiver(const QString& name) : Player(name) {}
    // Getters and setters for true color and it's location
    QColor getTrueColor() { return true_color; }
    void setTrueColor(QColor true_color) { this->true_color = true_color; }
    void setLocationofTrueColor(int row, int col) {
        this->row = row;
        this->col = col;
    }
    int getLocationofTrueColorX() { return row; }
    int getLocationofTrueColorY() { return col; }
private:
    QColor true_color; // True tile
    // True tile location
    int row;
    int col;
};


#endif // PLAYER_H
