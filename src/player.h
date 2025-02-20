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
std::string placePokemonOnBench(unsigned int index, int turn);
int switchActive();
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

// Accesseur
typeEnergy randomEnergy() const;
void printHand() const;
void showBoard() const;

Pokemon* activePokemon();
Hand* hand();
Deck* deck();
Bench* bench();

private:
    Deck* _deck;
    Hand* _hand;
    Pokemon* _activePokemon;
    Bench* _bench;
    int _victoryPoints;
};

#endif