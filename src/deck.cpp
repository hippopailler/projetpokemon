#include "deck.h"
#include <algorithm> 
#include <random> 
#include <chrono> 

Deck::Deck(std::vector<Card> cards, std::set<typeEnergy> energyTypes) :
    _cards(cards),  _energyTypes(energyTypes) {};

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

std::vector<Card> Deck::draw(int n){
    std::vector<Card> cards;
    for (int i = 0; i < n; i++){
        cards.push_back(draw());
    }
    return cards;
}

typeEnergy Deck::randomEnergy() const{
    std::vector<typeEnergy> energyTypes(_energyTypes.begin(), _energyTypes.end());
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::uniform_int_distribution<int> distribution(0, energyTypes.size() - 1);
    return energyTypes[distribution(e)];
}