#include "deck.h"
#include <algorithm> 
#include <random> 
#include <chrono> 
#include <iostream>
Deck::Deck(std::vector<Card> cards, std::vector<typeEnergy> energyTypes) :
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

typeEnergy Deck::randomEnergy() const{
    if (_energyTypes.empty()){
        throw std::runtime_error("No energy in the deck");
    }
    if (_energyTypes.size() == 1){
        return _energyTypes[0];
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::uniform_int_distribution<int> distribution(0, _energyTypes.size() - 1);
    typeEnergy energy = _energyTypes[0];
    return energy;
}

bool Deck::isEmpty() const{
    return _cards.empty();
}

unsigned int Deck::size() const{
    return _cards.size();
}