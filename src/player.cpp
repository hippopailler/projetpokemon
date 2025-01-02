#include "player.h"

Player::Player(Pokemon& pokemon)
    : _activePokemon(&pokemon), _victoryPoints(0){}

// Mutateurs
// void shuffleDeck();
// void draw();
// void switch_active(unsigned int position);
// void activeDamaged(unsigned int damage, energyType energy);
// void heal(Pokemon& pokemon, unsigned int amount);
void Player::attachEnergyActive(typeEnergy type){
    _activePokemon->attachEnergy(type);
}

void Player::attachEnergyActive(energyList energies){
    _activePokemon->attachEnergy(energies);
}

// void attachEnergyBench(energyType type, unsigned int slot);
// void attachEnergyBench(energyList energies, unsigned int slot);

void Player::detachEnergyActive(energyList energies){
    _activePokemon->detachEnergy(energies);
}

// Accesseurs

Pokemon* Player::activePokemon(){
    return _activePokemon;
}