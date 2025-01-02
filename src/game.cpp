#include "game.h"
#include <iostream>

Game::Game(Player* player1, Player* player2) {
    _players[0] = player1;
    _players[1] = player2;
    _activePlayer = 0;
    _turn = 0;
    _energyPlayed = false;
}
// Mutateur

void Game::endTurn(){
    _activePlayer = 1 - _activePlayer;
    _turn++;
    _energyPlayed = false;
}

void Game::attack(Move move){
    Pokemon* activePokemon = _players[_activePlayer]->activePokemon();
    Pokemon* opponentPokemon = _players[1 - _activePlayer]->activePokemon();
    bool canUse = (activePokemon->energyAttached()).enoughEnergy(move.cost());
    if (canUse){
        int dmg = activePokemon->attackWithMove(move);
        opponentPokemon->takeDamage(dmg);
        endTurn();
        return;
    }
    std::cout<< "Pas assez d'énergie\n";
    chooseAction();
}

void Game::attachEnergyActive(typeEnergy energy){
    if (_energyPlayed){
        std::cout << "Impossible d'attacher plusieurs énergie par tour\n";
        return;
    }
    _players[_activePlayer]->attachEnergyActive(energy);
    _energyPlayed = true;
}

void Game::chooseAction() {
    std::cout << "Choisissez une action :\n";
    std::cout << "1. Attacher une énergie\n";
    std::cout << "2. Attaquer\n";
    std::cout << "3. Finir le tour\n";
    int choice = 0;
    do {
        std::cout << "Choisissez votre action :";
        std::cin >> choice;
    } while (choice < 1 || choice > 3);
    switch (choice){
    case 1:{
        Pokemon* activePokemon = _players[_activePlayer]->activePokemon();
        attachEnergyActive(activePokemon->type()); //pour l'instant on attache la bonne énergie
        chooseAction();
        break;
    }
    case 2:{
        Pokemon* activePokemon = _players[_activePlayer]->activePokemon();
        Move move = activePokemon->chooseMove();
        attack(move);
        break;
    }
    case 3:
        endTurn();
        break;
    default:
        break;
    }
}

// Accesseur

unsigned int Game::turn() const{
    return _turn;
}

const Player* Game::current_player() const{
    return _players[_activePlayer];
}