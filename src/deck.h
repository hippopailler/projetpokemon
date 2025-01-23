#ifndef DECK
#define DECK

#include "card.h"
#include "energy.h"
#include <vector>
#include <memory>

class Deck {
public:
    Deck(std::vector<std::unique_ptr<Card>> cards, std::vector<typeEnergy> energyTypes);
    // Mutateurs
    void shuffle();
    std::unique_ptr<Card> draw();
    void addCard(std::unique_ptr<Card> card);
    // Accesseurs
    typeEnergy randomEnergy() const;
    bool isEmpty() const;
    unsigned int size() const;

private:
    std::vector<std::unique_ptr<Card>> _cards;
    const std::vector<typeEnergy> _energyTypes;
};

#endif