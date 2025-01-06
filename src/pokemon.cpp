#include "pokemon.h"
#include <iostream>

Pokemon::Pokemon(const std::string& name, int hp, const typeEnergy type, const typeEnergy weakness)
    : _name(name), _hp(hp), _type(type), _weakness(weakness), _energyAttached() {}

void Pokemon::takeDamage(const unsigned int damage) {
    _hp -= damage;
    if (_hp < 0) {
        _hp = 0; // Les points de vie ne peuvent pas être négatifs
    }
    std::cout << _name << " prend " << damage << " dégâts ! Il reste " << _hp << " HP.\n";
}

void Pokemon::addMove(const Move& move) {
    _moves.push_back(move); // Ajouter une attaque à la liste
}

Move Pokemon::chooseMove() {
    std::cout << "Choisissez une attaque pour " << _name << " :\n";
    for (size_t i = 0; i < _moves.size(); ++i) {
        std::cout << i + 1 << ". " << _moves[i].getName() << " (Puissance: " << _moves[i].getPower() << ")\n";
    }

    size_t choice;
    do {
        std::cout << "Entrez le numéro de l'attaque : ";
        std::cin >> choice;
    } while (choice < 1 || choice > _moves.size());

    return _moves[choice - 1];
}

int Pokemon::attackWithMove(Move move) {
    std::cout << _name << " utilise " << move.getName() << " !\n";
    return move.getPower() ; // Puissance de l'attaque + bonus d'attaque à gérer plus tard selon le type
}

void Pokemon::attachEnergy(typeEnergy energy){
    _energyAttached += energy;
}

void Pokemon::attachEnergy(energyList energies){
    _energyAttached += energies;
}

void Pokemon::detachEnergy(energyList energies){
    _energyAttached -= energies;
}

bool Pokemon::isFainted() const {
    return _hp <= 0;
}

std::string Pokemon::getName() const {
    return _name;
}

int Pokemon::getHP() const {
    return _hp;
}

bool Pokemon::canUseMove(Move move){
    return (_energyAttached.enoughEnergy(move.cost()));
}

energyList Pokemon::energyAttached(){
    return _energyAttached;
}

typeEnergy Pokemon::type(){
    return _type;
}

typeEnergy Pokemon::weakness() const{
    return _weakness;
}