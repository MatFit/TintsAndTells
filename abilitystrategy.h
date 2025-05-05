#ifndef ABILITYSTRATEGY_H
#define ABILITYSTRATEGY_H
#include <QString>

// ============================================================================
// Class: AbilityStrategy, DoublePointStrategy, TriplePointStrategy, NullifyOpponentPointsStrategy
// Pattern : Strategy
// Overview:
//   This class defines behavior in regards to abilities and their unique
//   functions. The goal here is to make abilities more of a plug in to
//   Guessers rather than integrated (decoupling)
// ============================================================================


class Guesser; // so player.h doesn't need to be included

class AbilityStrategy {
public:
    virtual ~AbilityStrategy() = default; // Base constructor
    virtual int modifyPoints(int basePoints) const = 0; // Base ability use
    virtual std::string getName() { return name; } // Getter for ability name
protected:
    std::string name; // Ability name
};


class DoublePointsStrategy : public AbilityStrategy {
public:
    // Set strategy name
    DoublePointsStrategy() {
        name = "2x Points";
    }
    // Use strategy
    int modifyPoints(int basePoints) const override {
        return basePoints * 2;
    }
};

class TriplePointsStrategy : public AbilityStrategy {
public:
    // Set strategy name
    TriplePointsStrategy() {
        name = "3x Points";
    }
    // Use strategy
    int modifyPoints(int basePoints) const override {
        return basePoints * 3;
    }
};

class NullifyOpponentPointsStrategy : public AbilityStrategy {
public:
    // Set strategy name
    NullifyOpponentPointsStrategy() {
        name = "Null Opponent's Points";
    }
    // No change to self just fulfill override
    int modifyPoints(int basePoints) const override {
        return basePoints;
    }
    // Sets to 0
    int returnToZero() const { return 0; }
};

#endif // ABILITYSTRATEGY_H
