#include "bench.h"
#include <iostream>

Bench::Bench():
    _cards{nullptr, nullptr, nullptr}{};

// Mutateurs
void Bench::placeOnBench(Pokemon& pokemon){
    for (auto& card : _cards) {
        if (card == NULL) {
            card = &pokemon;
            return;
        }
    }
    std::cout << "Le banc est plein" << std::endl;
}

void Bench::placeOnBench(Pokemon& pokemon, unsigned int index){
    if (_cards[index] == NULL) {
        _cards[index] = &pokemon;
    } else {
        std::cout << "Il y a déjà un pokémon sur l'emplacement " << index << std::endl;
    }
}

Pokemon* Bench::removeFromBench(unsigned int index){
    if (_cards[index] != NULL) {
        Pokemon* card = _cards[index];
        _cards[index] = NULL;
        return card;
    } else {
        std::cout << "Il n'y a pas de pokémon sur l'emplacement " << index << std::endl;
        return NULL;
    }
}

void Bench::attachEnergyBench(typeEnergy type, unsigned int slot){
    if (_cards[slot] != NULL) {
        _cards[slot]->attachEnergy(type);
    } else {
        std::cout << "Il n'y a pas de pokémon sur l'emplacement " << slot << std::endl;
    }
}

void Bench::attachEnergyBench(energyList energies, unsigned int slot){
    if (_cards[slot] != NULL) {
        _cards[slot]->attachEnergy(energies);
    } else {
        std::cout << "Il n'y a pas de pokémon sur l'emplacement " << slot << std::endl;
    }
}

void Bench::healBench(unsigned int amount, unsigned int index){
    if (_cards[index] != NULL) {
        _cards[index]->heal(amount);
    } else {
        std::cout << "Il n'y a pas de pokémon sur l'emplacement " << index << std::endl;
    }
}

// Accesseurs
std::array<Pokemon*, 3> Bench::cards() const{
    return _cards;
}

Pokemon& Bench::card(int index){
    return *_cards[index];
}

bool Bench::isEmpty() const{
    for (const auto& card : _cards) {
        if (card != nullptr) {
            return false;
        }
    }
    return true;
}

bool Bench::isFull() const{
    for (const auto& card : _cards) {
        if (card == nullptr) {
            return false;
        }
    }
    return true;
}

bool Bench::pokemonInSlot(unsigned int slot) const{
    return _cards[slot] != NULL;
}

unsigned int Bench::find(Pokemon& pokemon) const{
    for (unsigned int i = 0; i < 3; i++) {
        if (_cards[i] == &pokemon) {
            return i;
        }
    }
    std::cout << "Le pokémon n'est pas sur le banc" << std::endl;
    return 3;
}

void Bench::printBench() const{
    for (unsigned int i = 0; i < 3; i++) {
        if (_cards[i] != nullptr) {
            std::cout << "Emplacement " << i << ": " << _cards[i]->name() << std::endl;
        } else {
            std::cout << "Emplacement " << i << ": vide" << std::endl;
        }
    }
}