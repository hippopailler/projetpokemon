#ifndef PLAYER
#define PLAYER

#include "pokemon.h"
#include "energy.h"
#include <array>

class Player{
public:
    Player(Pokemon& pokemon);

// Mutateurs
// void shuffleDeck();
// void draw();
// void switch_active(unsigned int position);
// void activeDamaged(unsigned int damage, energyType energy);
// void heal(Pokemon& pokemon, unsigned int amount);
void attachEnergyActive(typeEnergy type);
void attachEnergyActive(energyList energies);
// void attachEnergyBench(energyType type, unsigned int slot);
// void attachEnergyBench(energyList energies, unsigned int slot);
void detachEnergyActive(energyList energies);


// Accesser

Pokemon* activePokemon();

private:
    //deck* _deck;
    // hand* _hand;
    Pokemon* _activePokemon;
    //std::array<Pokemon*, 3> _bench;
    int _victoryPoints;
};

#endif