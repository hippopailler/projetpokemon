#ifndef PLAYER
#define PLAYER

#include "pokemon.h"
#include "energy.h"
#include <array>
#include "hand.h"
#include "deck.h"

class Player{
public:
    Player(Deck& deck, Pokemon& pokemon);

// Mutateurs
void shuffleDeck();
void draw();
// void switch_active(unsigned int position);
void activeDamaged(unsigned int damage, typeEnergy energy);
// void heal(Pokemon& pokemon, unsigned int amount);
void attachEnergyActive(typeEnergy type);
void attachEnergyActive(energyList energies);
// void attachEnergyBench(energyType type, unsigned int slot);
// void attachEnergyBench(energyList energies, unsigned int slot);
void detachEnergyActive(energyList energies);


// Accesseur

Pokemon* activePokemon();
Hand* hand();
Deck* deck();

private:
    Deck* _deck;
    Hand* _hand;
    Pokemon* _activePokemon;
    //std::array<Pokemon*, 3> _bench;
    int _victoryPoints;
};

#endif