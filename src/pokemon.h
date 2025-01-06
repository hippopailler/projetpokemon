#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include "card.h"
#include "energy.h"
#include "move.h"

class Pokemon: public Card{
public:
    Pokemon(const std::string& name, int hp, const typeEnergy type, const typeEnergy weakness);

    void takeDamage(int damage);
    int attackWithMove(Move move);
    void addMove(const Move& move); // Ajouter une attaque au Pokémon
    Move chooseMove();
    void attachEnergy(typeEnergy);
    void attachEnergy(energyList);
    void detachEnergy(energyList);
    bool isFainted() const;

    std::string getName() const;
    typeEnergy _weakness() const;
    int getHP() const;
    bool canUseMove(Move move);
    energyList energyAttached();
    typeEnergy type();

private:
    std::string _name;
    int _hp;
    const typeEnergy _type;
    const typeEnergy _weakness;
    std::vector<Move> _moves; // Liste d'attaques
    energyList _energyAttached;
};

#endif