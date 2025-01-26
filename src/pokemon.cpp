#include "pokemon.h"
#include <iostream>

Pokemon::Pokemon(pokemonData data) :
    Card(cardClass::POKEMON), _data(data), _hp(data.hp), _energyAttached() {}

void Pokemon::takeDamage(const unsigned int damage) {
    int realDamage = damage > _hp ? _hp : damage;
    _hp -= realDamage;
    std::cout << _data.name << " prend " << damage << " dégâts ! Il reste " << _hp << " HP.\n";
}

Move Pokemon::chooseMove() {
    std::cout << "Choisissez une attaque pour " << _data.name << " :\n";
    for (size_t i = 0; i < _data.moves.size(); ++i) {
        std::cout << i + 1 << ". " << _data.moves[i].getName() << " (Puissance: " << _data.moves[i].getPower() << ")\n";
    }

    size_t choice;
    do {
        std::cout << "Entrez le numéro de l'attaque : ";
        std::cin >> choice;
    } while (choice < 1 || choice > _data.moves.size());

    return _data.moves[choice - 1];
}

int Pokemon::attackWithMove(Move move) {
    std::cout << _data.name << " utilise " << move.getName() << " !\n";
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

void Pokemon::heal(unsigned int amount){
    _hp + amount > _data.hp ? _hp = _data.hp : _hp += amount;
}

void Pokemon::onPlayed(unsigned int turn){
    _turnPlayed = turn;
}

void Pokemon::evolve(Pokemon* evolution, unsigned int turn){
    unsigned int missingHP = _data.hp - _hp;
    _data = evolution->_data;
    _hp = evolution->_hp - missingHP;
    _turnPlayed = turn;
    //delete evolution;
}

// Accesseurs

std::string Pokemon::cardID() const{
    return _data.cardID;
}

std::string Pokemon::name() const {
    return _data.name;
}

unsigned int Pokemon::hp() const {
    return _hp;
}

unsigned int Pokemon::maxHP() const {
    return _data.hp;
}

bool Pokemon::canUseMove(Move move){
    return (_energyAttached.enoughEnergy(move.cost()));
}

bool Pokemon::canRetreat(){
    return (_energyAttached.enoughEnergy(_data.retreatCost));
}

energyList Pokemon::retreatCost() const{
    return _data.retreatCost;
}

energyList Pokemon::energyAttached(){
    return _energyAttached;
}

typeEnergy Pokemon::type(){
    return _data.type;
}

typeEnergy Pokemon::weakness() const{
    return _data.weakness;
}

int Pokemon::turnPlayed() const{
    return _turnPlayed;
}

unsigned int Pokemon::missingHP() const{
    return _data.hp - _hp;
}

bool Pokemon::canEvolve(unsigned int turn, std::string name){
    if (turn <= _turnPlayed){
        std::cout << "Il faut attendre un tour pour évoluer\n";
        return false;
    }
    if (_data.name == name){
        return true;
    }
    std::cout << "Les pokemons ne sont pas compatibles\n";
    return false;
}

std::optional <std::string> Pokemon::evolveFrom() const{
    return _data.evolveFrom;
}

bool Pokemon::isBasic() const{
    return !_data.evolveFrom.has_value();
}