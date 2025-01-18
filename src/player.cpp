#include "player.h"

Player::Player(Deck& deck, Pokemon& pokemon)
    : _deck(&deck), _hand(new Hand()), _activePokemon(&pokemon), _bench(), _victoryPoints(0){}

// Mutateurs
void Player::shuffleDeck(){
    _deck->shuffle();
}

void Player::draw(){
    Card& card = _deck->draw();
    _hand->addCard(card);
}

void Player::placeOnBench(Pokemon& pokemon){
    _bench->placeOnBench(pokemon);
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

void Player::attachEnergyBench(typeEnergy type, unsigned int slot){
    _bench->attachEnergyBench(type, slot);
}

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