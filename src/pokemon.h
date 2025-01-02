#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include "energy.h"
#include "move.h"

class Pokemon {
public:
    Pokemon(const std::string& name, int hp, const typeEnergy type);

    void takeDamage(int damage);
    int attackWithMove(Move move);
    void addMove(const Move& move); // Ajouter une attaque au Pokémon
    Move chooseMove();
    void attachEnergy(typeEnergy);
    bool isFainted() const;

    std::string getName() const;
    int getHP() const;
    bool canUseMove(Move move);

private:
    std::string _name;
    int _hp;
    const typeEnergy _type;
    std::vector<Move> _moves; // Liste d'attaques
    energyList _energyAttached;
};

#endif