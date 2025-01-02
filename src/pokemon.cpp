#include "pokemon.h"
#include <iostream>

Pokemon::Pokemon(const std::string& name, int hp, const std::string& type)
    : _name(name), _hp(hp), _type(type) {}

void Pokemon::takeDamage(int damage) {
    int actualDamage = damage;
    if (actualDamage < 0) {
        actualDamage = 0; // Minimum 0 dégâts
    }
    _hp -= actualDamage;
    if (_hp < 0) {
        _hp = 0; // Les points de vie ne peuvent pas être négatifs
    }
    std::cout << _name << " prend " << actualDamage << " dégâts ! Il reste " << _hp << " HP.\n";
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

bool Pokemon::isFainted() const {
    return _hp <= 0;
}

std::string Pokemon::getName() const {
    return _name;
}

int Pokemon::getHP() const {
    return _hp;
}
