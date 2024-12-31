#include "pokemon.h"
#include <iostream>

Pokemon::Pokemon(const std::string& name, int hp, const std::string& type)
    : name(name), hp(hp), type(type) {}

void Pokemon::takeDamage(int damage) {
    int actualDamage = damage;
    if (actualDamage < 0) {
        actualDamage = 0; // Minimum 0 dégâts
    }
    hp -= actualDamage;
    if (hp < 0) {
        hp = 0; // Les points de vie ne peuvent pas être négatifs
    }
    std::cout << name << " prend " << actualDamage << " dégâts ! Il reste " << hp << " HP.\n";
}

void Pokemon::addMove(const Move& move) {
    moves.push_back(move); // Ajouter une attaque à la liste
}

Move Pokemon::chooseMove() {
    std::cout << "Choisissez une attaque pour " << name << " :\n";
    for (size_t i = 0; i < moves.size(); ++i) {
        std::cout << i + 1 << ". " << moves[i].getName() << " (Puissance: " << moves[i].getPower() << ")\n";
    }

    size_t choice;
    do {
        std::cout << "Entrez le numéro de l'attaque : ";
        std::cin >> choice;
    } while (choice < 1 || choice > moves.size());

    return moves[choice - 1];
}

int Pokemon::attackWithMove(Move move) {
    std::cout << name << " utilise " << move.getName() << " !\n";
    return move.getPower() ; // Puissance de l'attaque + bonus d'attaque à gérer plus tard selon le type
}

bool Pokemon::isFainted() const {
    return hp <= 0;
}

std::string Pokemon::getName() const {
    return name;
}

int Pokemon::getHP() const {
    return hp;
}
