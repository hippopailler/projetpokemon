#include "player.h"

Player::Player(Deck& deck, Pokemon& pokemon)
    : _deck(&deck), _hand(new Hand()), _activePokemon(&pokemon), _victoryPoints(0){}

// Mutateurs
void Player::shuffleDeck(){
    _deck->shuffle();
}

void Player::draw(){
    Card& card = _deck->draw();
    _hand->addCard(card);
}

// void switch_active(unsigned int position);

void Player::activeDamaged(unsigned int damage, typeEnergy energy){
    const int finalDamage = (_activePokemon->weakness() == energy? damage + 20 : damage);
    _activePokemon->takeDamage(finalDamage);
}

// void heal(Pokemon& pokemon, unsigned int amount);
void Player::attachEnergyActive(typeEnergy type){
    _activePokemon->attachEnergy(type);
};

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

Hand* Player::hand(){
    return _hand;
}