#ifndef GAME
#define GAME

#include"player.h"
#include"move.h"
#include"energy.h"
#include<array>

class Game{
public:
    Game(Player*, Player*);
    void draw();
    void endTurn();
    void attack(Move);
    void attachEnergyActive(typeEnergy);
    void attachEnergyBench(typeEnergy, unsigned int);
    void placeOnBench(Pokemon&);
    //void retreat(??);
    //fin de la game??
    void chooseAction();

// Accesseurs
    unsigned int turn() const;
    const Player* current_player() const;

private:
    unsigned int _turn;
    int _activePlayer;
    std::array<Player*, 2> _players;
    bool _energyPlayed;
};

#endif