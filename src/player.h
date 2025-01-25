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
    Player(Deck& deck);

// Mutateurs
void shuffleDeck();
void draw();
void draw(unsigned int amount);
void placeActivePokemon(unsigned int index, int turn);
void placePokemonOnBench(unsigned int index, int turn);
void switchActive();
void switchActive(unsigned int position);
void activeDamaged(unsigned int damage, typeEnergy energy);
// void heal(Pokemon& pokemon, unsigned int amount);
void attachEnergyActive(typeEnergy type);
void attachEnergyActive(energyList energies);
void attachEnergyBench(typeEnergy type, unsigned int slot);
// void attachEnergyBench(energyList energies, unsigned int slot);
void detachEnergyActive(energyList energies);
void handToDeck();
void mulligan();
void gainPoints(unsigned int);

// Accesseur
typeEnergy randomEnergy() const;
void printHand() const;
void showBoard() const;
bool hasWon() const;

Pokemon* activePokemon();
Hand* hand();
Deck* deck();
Bench* bench();
unsigned int victoryPoints();

private:
    Deck* _deck;
    Hand* _hand;
    Pokemon* _activePokemon;
    Bench* _bench;
    unsigned int _victoryPoints;
};

#endif