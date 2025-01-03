#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include "move.h"

class Pokemon {
public:
    Pokemon(const std::string& name, int hp, const std::string& type);

    void takeDamage(int damage);
    int attackWithMove(Move move);
    void addMove(const Move& move); // Ajouter une attaque au Pokémon
    Move chooseMove();
    bool isFainted() const;

    std::string getName() const;
    int getHP() const;

private:
    std::string name;
    int hp;
    const std::string& type;
    std::vector<Move> moves; // Liste d'attaques
};

#endif