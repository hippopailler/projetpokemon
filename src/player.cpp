#include "player.h"
#include <iostream>

Player::Player(Deck& deck)
    : _deck(&deck), _hand(new Hand()), _activePokemon(NULL), _bench(new Bench()), _victoryPoints(0) {}

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

void Player::placeActivePokemon(unsigned int index, int turn) {
    if (index >= _hand->size()) {
        std::cout << "Index invalide" << std::endl;
        return;
    }
    std::unique_ptr<Card> card = _hand->takeCard(index);
    Pokemon* pokemon = dynamic_cast<Pokemon*>(card.get());
    if (pokemon) {
        _activePokemon = pokemon;
        pokemon->onPlayed(turn);
        card.release();
    } else {
        std::cout << "La carte sélectionnée n'est pas un Pokemon" << std::endl;
        _hand->addCard(std::move(card));
    }
}

std::string Player::placePokemonOnBench(unsigned int index, int turn) {
    std::unique_ptr<Card> card = _hand->takeCard(index);
    Pokemon* pokemon = dynamic_cast<Pokemon*>(card.get());
    _bench->placeOnBench(*pokemon);
    pokemon->onPlayed(turn);
    card.release(); 
    return pokemon->cardID();
}

void Player::switchActive() {
    unsigned int position;
    do  {
        _bench->printBench();
        std::cout << "Choisir le prochain pokemon actif :";
        std::cin >> position;
    } while (position >= 3 || _bench->pokemonInSlot(position) == false);
    switchActive(position);
}

void Player::switchActive(unsigned int position) {
    std::unique_ptr<Pokemon> temp(_activePokemon);
    _activePokemon = _bench->removeFromBench(position).release();
    _bench->placeOnBench(std::move(temp), position);
}

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

void Player::mulligan() {
    handToDeck();
    draw(5);
}

// Accesseurs

typeEnergy Player::randomEnergy() const {
    return _deck->randomEnergy();
}

void Player::printHand() const {
    _hand->printHand();
}

void Player::showBoard() const {
    std::cout << "Pokemon actif : " << _activePokemon->name() << " "
        << _activePokemon->hp() << "/" << _activePokemon->maxHP() << " PV" << std::endl;
    _bench->printBench();
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

Bench* Player::bench() {
    return _bench;
}