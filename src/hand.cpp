#include "hand.h"
#include "pokemon.h"
#include <iostream>

void Hand::addCard(std::unique_ptr<Card> card) {
    _cards.push_back(std::move(card));
}

std::unique_ptr<Card> Hand::takeCard(const int index) {
    std::unique_ptr<Card> card = std::move(_cards[index]);
    _cards.erase(_cards.begin() + index);
    return card;
}

void Hand::removeCard(const int index) {
    _cards.erase(_cards.begin() + index);
}

void Hand::handToDeck(Deck& deck){
    while (!_cards.empty()){
        deck.addCard(std::move(_cards.back()));
        _cards.pop_back();
    }
}

const std::vector<std::unique_ptr<Card>>& Hand::cards() const {
    return _cards;
}

bool Hand::hasPokemonCard() const {
    for (const auto& card : _cards) {
        if (dynamic_cast<Pokemon*>(card.get())) {
            return true;
        }
    }
    return false;
}

void Hand::printHand() const {
    std::cout << "Main :\n";
    for (unsigned int i = 0; i < _cards.size(); i++) {
        std::cout << i << ". " << _cards[i]->name() << "\n";
    }
}

unsigned int Hand::size() const {
    return _cards.size();
}