#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move {
public:
    Move(const std::string& name, int power);

    std::string getName() const;
    int getPower() const;

private:
    std::string name;
    int power;
};

#endif