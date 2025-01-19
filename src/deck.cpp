#include "deck.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

Deck::Deck(std::vector<std::unique_ptr<Card>> cards, std::vector<typeEnergy> energyTypes) :
    _cards(std::move(cards)), _energyTypes(energyTypes) {}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(_cards.begin(), _cards.end(), e);
}

std::unique_ptr<Card> Deck::draw() {
    if (_cards.empty()) {
        throw std::runtime_error("No cards left in the deck");
    }
    std::unique_ptr<Card> card = std::move(_cards.back());
    _cards.pop_back();
    return card;
}

typeEnergy Deck::randomEnergy() const {
    if (_energyTypes.empty()) {
        throw std::runtime_error("No energy in the deck");
    }
    if (_energyTypes.size() == 1) {
        return _energyTypes[0];
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::uniform_int_distribution<int> distribution(0, _energyTypes.size() - 1);
    return _energyTypes[distribution(e)];
}

bool Deck::isEmpty() const {
    return _cards.empty();
}

unsigned int Deck::size() const {
    return _cards.size();
}