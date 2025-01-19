#ifndef HAND
#define HAND

#include "card.h"
#include <vector>
#include <memory>

class Hand {
public:
    // Mutateurs
    void addCard(std::unique_ptr<Card> card);
    void removeCard(const int index);

    // Accesseur
    void printHand() const;
    std::vector<std::unique_ptr<Card>> cards() const;

private:
    std::vector<std::unique_ptr<Card>> _cards;
};

#endif