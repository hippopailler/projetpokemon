#ifndef CARD
#define CARD

#include <string>

enum class cardClass{
    POKEMON,
    ITEM,
    TRAINER
};

class Card{
public:
    Card(cardClass cardType) : _cardType(cardType) {}

    bool isPokemon() const{
        return _cardType == cardClass::POKEMON;
    };

    virtual std::string cardID() const = 0;

    virtual std::string name() const = 0;

    cardClass cardType(){ return _cardType;}

private:
    cardClass _cardType;
};

#endif