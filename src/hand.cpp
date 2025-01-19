#include "hand.h"
#include <iostream>

void Hand::addCard(const Card& card){
    _cards.push_back(card);
}

void Hand::removeCard(const int index){
    _cards.erase(_cards.begin() + index);
}

std::vector<Card> Hand::cards() const{
    return _cards;
}

void Hand::printHand() const{
    std::cout << "Main :\n";
    for (unsigned int i = 0; i < _cards.size(); i++){
        std::cout << i << ". " << _cards[i].name() << "\n";
    }
}