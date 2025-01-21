#ifndef HAND
#define HAND

#include "card.h"
#include "deck.h"
#include <vector>
#include <memory>

class Hand {
public:
    // Mutateurs
    void addCard(std::unique_ptr<Card> card);
    void removeCard(const int index);
    void handToDeck(Deck& deck);

    // Accesseur
    void printHand() const;
    const std::vector<std::unique_ptr<Card>>& cards() const;
    bool hasPokemonCard() const;
    unsigned int size() const;

private:
    std::vector<std::unique_ptr<Card>> _cards;
};

#endif