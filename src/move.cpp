#include "move.h"

Move::Move(const std::string& name, int power)
    : _name(name), _power(power) {}

std::string Move::getName() const {
    return _name;
}

int Move::getPower() const {
    return _power;
}