#ifndef BENCH
#define BENCH

#include "pokemon.h"
#include <array>
class Bench{
public:
    Bench();

// Mutateurs
    void placeOnBench(Pokemon&);
    void placeOnBench(Pokemon&, unsigned int);
    Pokemon* removeFromBench(unsigned int);
    void attachEnergyBench(typeEnergy type, unsigned int slot);
    void attachEnergyBench(energyList energies, unsigned int slot);
    void healBench(unsigned int amount, unsigned int index);


// Accesseurs
    std::array<Pokemon*, 3> cards() const;
    Pokemon& card(int index);
    bool isEmpty() const;
    bool isFull() const;
    unsigned int find(Pokemon& pokemon) const;
    void printBench() const;


private:
    std::array<Pokemon*, 3> _cards;
};

#endif