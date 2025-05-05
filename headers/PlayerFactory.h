#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H
#include "player.h"   // your Player, Guesser, QGiver definitions
#include <QString>
#include <QColor>

// ============================================================================
// Class: PlayerFactory
// Pattern: Factory
// Overview:
//   This class handles instantiated different types of player classes
// ============================================================================

// Enum to specify the type
enum class PlayerType {
    Guesser,
    QGiver
};

class PlayerFactory {
public:
    // createTile() is a method to handle instantiating players
    static Player* createPlayer(PlayerType type, const QString& name, const QColor& color = QColor())
    {
        switch (type) {
        case PlayerType::Guesser:
            return new Guesser(name, color);
        case PlayerType::QGiver:
            return new QGiver(name);
        }
        return nullptr;
    }
};

#endif // PLAYERFACTORY_H
