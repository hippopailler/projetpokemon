#include "deck.h"
#include <algorithm> 
#include <random> 
#include <chrono> 

Deck::Deck(std::vector<Card> cards):
    _cards(cards) {};

void Deck::shuffle(){
    // Ici c'est possible de remplacer seed par un entier fixe pour fixer la RNG (tests)
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(_cards.begin(), _cards.end(), e);
}

Card& Deck::draw(){
    Card& card = _cards.back();
    _cards.pop_back();
    return card;
}