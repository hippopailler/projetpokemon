#ifndef PKMIA
#define PKMIA

#include "game.h"

class pkmIA
{
public:
    pkmIA(unsigned int player);
    void play(Game *game);

private:
    unsigned int _player;
};

#endif