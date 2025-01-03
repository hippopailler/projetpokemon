#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& name);
    Player(); // Constructeur par défaut
    std::string getName() const;

private:
    std::string name;
};

#endif // PLAYER_H