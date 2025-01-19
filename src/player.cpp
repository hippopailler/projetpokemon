#include "player.h"
#include <iostream>

Player::Player(Deck& deck, Pokemon& pokemon)
    : _deck(&deck), _hand(new Hand()), _activePokemon(&pokemon), _bench(), _victoryPoints(0) {}

// Mutateurs
void Player::shuffleDeck() {
    _deck->shuffle();
}

void Player::draw() {
    if (_deck->isEmpty()) {
        std::cout << "Le deck est vide" << std::endl;
        return;
    }
    std::unique_ptr<Card> card = _deck->draw();
    _hand->addCard(std::move(card));
}

void Player::draw(unsigned int n) {
    n > _deck->size() ? n = _deck->size() : n;
    for (unsigned int i = 0; i < n; i++) {
        draw();
    }
}

void Player::placeOnBench(Pokemon& pokemon) {
    _bench->placeOnBench(pokemon);
}

// void switch_active(unsigned int position);

void Player::activeDamaged(unsigned int damage, typeEnergy energy) {
    const int finalDamage = (_activePokemon->weakness() == energy ? damage + 20 : damage);
    _activePokemon->takeDamage(finalDamage);
}

// void heal(Pokemon& pokemon, unsigned int amount);
void Player::attachEnergyActive(typeEnergy type) {
    _activePokemon->attachEnergy(type);
}

void Player::attachEnergyActive(energyList energies) {
    _activePokemon->attachEnergy(energies);
}

void Player::attachEnergyBench(typeEnergy type, unsigned int slot) {
    _bench->attachEnergyBench(type, slot);
}

// void attachEnergyBench(energyList energies, unsigned int slot);

void Player::detachEnergyActive(energyList energies) {
    _activePokemon->detachEnergy(energies);
}

void Player::handToDeck() {
    _hand->handToDeck(*_deck);
}

// Accesseurs

typeEnergy Player::randomEnergy() const {
    return _deck->randomEnergy();
}

void Player::printHand() const {
    _hand->printHand();
}

Pokemon* Player::activePokemon() {
    return _activePokemon;
}

Hand* Player::hand() {
    return _hand;
}

Deck* Player::deck() {
    return _deck;
}