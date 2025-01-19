#ifndef DECK
#define DECK

#include "card.h"
#include "energy.h"
#include <vector>

class Deck{
public:
    Deck(std::vector<Card> cards, std::vector<typeEnergy> energyTypes);
// Mutateurs
    void shuffle();
    Card& draw();
// Accesseurs
    typeEnergy randomEnergy() const;
    bool isEmpty() const;
    unsigned int size() const;

private:
    std::vector<Card> _cards;
    const std::vector<typeEnergy> _energyTypes;
};

#endif