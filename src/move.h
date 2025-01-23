#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "energy.h"

class Move {
public:
    Move(const std::string& name, int power);
    Move(const std::string& name, int power, energyList cost);

    std::string getName() const;
    unsigned int getPower() const;
    energyList cost() const;

private:
    std::string _name;
    unsigned int _power;
    energyList _cost;

};

#endif