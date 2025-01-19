#ifndef HAND
#define HAND

#include "card.h"
#include <vector>

class Hand{
public:
    

    // Mutateurs
    void addCard(const Card& card);
    void removeCard(const int index);

    // Accesseur
    void printHand() const;
    std::vector<Card> cards() const;

private:
    std::vector<Card> _cards;
};

#endif