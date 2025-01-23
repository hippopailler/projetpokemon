#include "move.h"

Move::Move(const std::string& name, int power)
    : _name(name), _power(power), _cost() {}

Move::Move(const std::string& name, int power, energyList cost)
    : _name(name), _power(power), _cost(cost) {}

std::string Move::getName() const {
    return _name;
}

unsigned int Move::getPower() const {
    return _power;
}

energyList Move::cost() const{
    return _cost;
}