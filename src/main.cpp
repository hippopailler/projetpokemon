#include "GameRenderGr.h"   // Pour la partie graphique
#include "pokemon.h"        // Fichiers de la logique
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
#include <thread>           // Pour exécuter plusieurs threads
#include <unistd.h>         // Pour la gestion du temps

// Fonction pour la logique du jeu (terminal)
void runLogic(Game& game) {
    game.beginGame();  // Lancer la logique
}

// Fonction pour la fenêtre graphique
void runGraphics(Game& game) {
    GameRenderGr gameRender(&game);  // Initialise la fenêtre graphique avec la logique
    gameRender.updateActiveHPTexts();  // Synchronise les textes
    gameRender.run();  // Démarre la boucle principale graphique
}

int main() {
    // Initialisation des données
    pokemonData dataBulb = getPokemonData("A1#001");
    pokemonData dataChen = getPokemonData("A1#005");
    Pokemon bulbizarre = Pokemon(dataBulb);
    Pokemon chenipan = Pokemon(dataChen);

    Deck deck1 = getDeck("/home/hippolyte/projet_c++/src/db/data/decks/deck1.json");
    Deck deck2 = getDeck("/home/hippolyte/projet_c++/src/db/data/decks/deck1.json");

    Player player1(deck1);
    Player player2(deck2);

    Game game(&player1, &player2);

    // Création des threads pour exécuter en parallèle
    std::thread logicThread(runLogic, std::ref(game));  // Thread pour la logique
    std::thread graphicsThread(runGraphics, std::ref(game));  // Thread pour la fenêtre graphique

    // Attendre la fin des deux threads
    logicThread.join();
    graphicsThread.join();

    return 0;
}
