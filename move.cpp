#include "move.h"

Move::Move(const std::string& name, int power)
    : name(name), power(power) {}

std::string Move::getName() const {
    return name;
}

int Move::getPower() const {
    return power;
}