#ifndef GAME
#define GAME

#include"player.h"
#include"move.h"
#include"energy.h"
#include"pokemon.h"
#include"color.hpp"
#include<array>

class Game{
public:
    Game(Player*, Player*);
    void draw();
    void endTurn();
    void attack(Move);
    void attachEnergyActive(typeEnergy);
    void attachEnergyBench(typeEnergy, unsigned int);
    void retreat();
    //fin de la game??
    void chooseAction();
    void beginTurn();
    void placeActivePokemon(int);
    void placePokemonOnBench();
    void beginGame();
    void evolve();

// Accesseurs
    unsigned int turn() const;
    const Player* current_player() const;

private:
    unsigned int _turn;
    int _activePlayer;
    std::array<Player*, 2> _players;
    bool _energyPlayed;
    int _winner;
    typeEnergy _energy;
};

#endif