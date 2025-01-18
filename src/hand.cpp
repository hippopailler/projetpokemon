#include "hand.h"

std::vector<Card> Hand::cards() const{
    return _cards;
}

void Hand::addCard(const Card& card){
    _cards.push_back(card);
}

void Hand::removeCard(const int index){
    _cards.erase(_cards.begin() + index);
}