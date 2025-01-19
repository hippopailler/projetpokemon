#include "hand.h"
#include <iostream>

void Hand::addCard(std::unique_ptr<Card> card) {
    _cards.push_back(std::move(card));
}

void Hand::removeCard(const int index) {
    _cards.erase(_cards.begin() + index);
}

std::vector<std::unique_ptr<Card>> Hand::cards() const {
    std::vector<std::unique_ptr<Card>> copy;
    for (const auto& card : _cards) {
        copy.push_back(std::make_unique<Card>(*card));
    }
    return copy;
}

void Hand::printHand() const {
    std::cout << "Main :\n";
    for (unsigned int i = 0; i < _cards.size(); i++) {
        std::cout << i << ". " << _cards[i]->name() << "\n";
    }
}