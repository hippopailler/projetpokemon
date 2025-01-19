#ifndef PLAYER
#define PLAYER

#include "pokemon.h"
#include "energy.h"
#include <array>
#include "hand.h"
#include "deck.h"
#include "bench.h"

class Player{
public:
    Player(Deck& deck, Pokemon& pokemon);

// Mutateurs
void shuffleDeck();
void draw();
void draw(unsigned int amount);
void placeOnBench(Pokemon& pokemon);
// void switch_active(unsigned int position);
void activeDamaged(unsigned int damage, typeEnergy energy);
// void heal(Pokemon& pokemon, unsigned int amount);
void attachEnergyActive(typeEnergy type);
void attachEnergyActive(energyList energies);
void attachEnergyBench(typeEnergy type, unsigned int slot);
// void attachEnergyBench(energyList energies, unsigned int slot);
void detachEnergyActive(energyList energies);
typeEnergy randomEnergy() const;

// Accesseur
void printHand() const;

Pokemon* activePokemon();
Hand* hand();
Deck* deck();

private:
    Deck* _deck;
    Hand* _hand;
    Pokemon* _activePokemon;
    Bench* _bench;
    int _victoryPoints;
};

#endif