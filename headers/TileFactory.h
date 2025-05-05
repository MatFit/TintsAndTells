#ifndef TILEFACTORY_H
#define TILEFACTORY_H
#include "tiles.h"


// ============================================================================
// Class: TileFactory
// Pattern: Factory
// Overview:
//   This class handles instantiated different types of tile classes
// ============================================================================

// Enum to specify the type
enum class TileType {
    Color,
    Progress
};

class TileFactory {
public:
    // createTile() is a method to handle instantiating tiles
    static Tile* createTile(TileType type, int size, QGraphicsItem* parent = nullptr) {
        switch (type) {
        case TileType::Color:
            return new ColorTile(size, parent);
        case TileType::Progress:
            return new ProgressTile(size, parent);
        default:
            return new Tile(size, parent);
        }
    }
};

#endif // TILEFACTORY_H
