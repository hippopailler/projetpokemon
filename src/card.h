#ifndef CARD
#define CARD

#include <string>

class Card{
public:
    std::string cardID() const{
        return _cardID;
    }
    std::string name() const{
        return _name;
    }
private:
    std::string _cardID;
    std::string _name;
};

#endif