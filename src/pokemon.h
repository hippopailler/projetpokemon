#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include "card.h"
#include "energy.h"
#include "move.h"
#include <optional>
#include <climits>

struct pokemonData{
    std::string cardID;
    std::string name;
    unsigned int hp;
    typeEnergy type;
    typeEnergy weakness;
    energyList retreatCost;
    bool isEx;
    std::vector<Move> moves;
    std::optional<std::string> evolveFrom;
};

class Pokemon: public Card{
public:
    Pokemon(pokemonData data);

    void takeDamage(const unsigned int damage);
    int attackWithMove(Move move);
    Move chooseMove();
    void attachEnergy(typeEnergy);
    void attachEnergy(energyList);
    void detachEnergy(energyList);
    bool isFainted() const;
    void heal(unsigned int amount);
    void onPlayed(unsigned int);
    void evolve(Pokemon*, unsigned int);

// Accesseurs

    std::string cardID() const;
    std::string name() const;
    typeEnergy weakness() const;
    unsigned int hp() const;
    unsigned int maxHP() const;
    bool canUseMove(Move move);
    bool canRetreat();
    energyList energyAttached();
    typeEnergy type();
    int turnPlayed() const;
    unsigned int missingHP() const;
    bool canEvolve(unsigned int, std::string);
    std::optional<std::string> evolveFrom() const;
    bool isBasic() const;
    bool isEx() const;

private:
    pokemonData _data;
    unsigned int _hp;
    energyList _energyAttached;
    unsigned int _turnPlayed {UINT_MAX};
};

#endif