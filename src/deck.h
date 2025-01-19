#ifndef DECK
#define DECK

#include "card.h"
#include "energy.h"
#include <vector>
#include <set>

class Deck{
public:
    Deck(std::vector<Card> cards, std::set<typeEnergy> energyTypes);
// Mutateurs
    void shuffle();
    Card& draw();
    std::vector<Card> draw(int);
// Accesseurs
    std::vector<Card> cards() const;
    typeEnergy randomEnergy() const;

private:
    std::vector<Card> _cards;
    std::set<typeEnergy> _energyTypes;
};

#endif