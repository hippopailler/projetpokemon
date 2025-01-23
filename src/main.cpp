#include "pokemon.h"
#include "move.h"
#include "energy.h"
#include "player.h"
#include "game.h"
#include "deck.h"
#include "hand.h"
#include "bench.h"
#include "card.h"
#include "db/gettingPokemonData.hpp"
#include <iostream>

int main() {

    pokemonData dataBulb = getPokemonData("A1#001");
    pokemonData dataChen = getPokemonData("A1#005");
    Pokemon bulbizarre = Pokemon(dataBulb);
    Pokemon chenipan = Pokemon(dataChen);

//    Deck deck1({Card(bulbizarre), Card(chenipan)});
    Deck deck1 = getDeck("db/data/decks/deck1.json");
    Deck deck2 = getDeck("db/data/decks/deck1.json");

    Player player1(deck1);
    Player player2(deck2);

    Game game(&player1, &player2);
    //game.beginTurn();
    game.beginGame();

/*
    Pokemon pikachu("Pikachu", 100, LIGHTING);
    Pokemon charmander("Salamèche", 120, FIRE);

        // Ajout des attaques
    std::vector<typeEnergy> thunderCost = {LIGHTING};
    pikachu.addMove(Move("Tonnerre", 50, thunderCost));
    pikachu.addMove(Move("Queue de Fer", 40));

    charmander.addMove(Move("Flammeche", 45));
    charmander.addMove(Move("Griffe", 35));

    Player player1(pikachu);
    Player player2(charmander);
    Game game(&player1, &player2);

    while (!pikachu.isFainted() && !charmander.isFainted()){
        game.chooseAction();
    }
    */
    
    return 0;
}
