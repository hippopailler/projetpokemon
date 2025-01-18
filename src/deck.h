#ifndef DECK
#define DECK

#include "card.h"
#include <vector>

class Deck{
public:
    Deck(std::vector<Card> cards);
// Mutateurs
    void shuffle();
    Card& draw();
    void draw(int);
// Accesseurs
    std::vector<Card> cards() const;
private:
    std::vector<Card> _cards;
};

#endif