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
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

// Fonction pour la logique du jeu (terminal)
void runLogic(Game& game, GameGr& gameRender) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{ return ready; });
    gameRender.updateActiveHPTexts(50, 1);
    game.beginGame();  // Lancer la logique
}

//Fonction pour la fenêtre graphique 
void runGraphics(Game& game, GameGr& gameRender) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all();
    gameRender.run();  // Démarre la boucle principale graphique
}

int main() {
    // Initialisation des données
    pokemonData dataBulb = getPokemonData("A1#001");
    pokemonData dataChen = getPokemonData("A1#005");
    Pokemon bulbizarre = Pokemon(dataBulb);
    Pokemon chenipan = Pokemon(dataChen);

    Deck deck1 = getDeck("./src/db/data/decks/deck1.json");
    Deck deck2 = getDeck("./src/db/data/decks/deck1.json");

    Player player1(deck1);
    Player player2(deck2);

    Game game(&player1, &player2);
    GameGr gameRender;

    // Création des threads pour exécuter en parallèle
    std::thread logicThread(runLogic, std::ref(game), std::ref(gameRender));  // Thread pour la logique
 
    runGraphics(game, gameRender);  // Thread pour la fenêtre graphique
    // Attendre la fin des deux threads
    logicThread.join();

    return 0;
}
