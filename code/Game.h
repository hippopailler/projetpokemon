#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Card.h"
#include "Player.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Player player1;
    Player player2;
    std::vector<sf::Sprite> cardSprites;
    sf::Texture cardTexture;
    std::vector<Card> hand; // Main de cartes du joueur
    void addCard(const std::string& cardName, float x, float y);

    //CardManager cardManager;
    
    std::vector<sf::Sprite> playerHand;     // Cartes du joueur (dos visible)
    std::vector<sf::Sprite> opponentHand;


    void initializeHands(int playerCardCount, int opponentCardCount); // Initialiser les mains
    void updatePlayerHand(int cardCount); // Modifier dynamiquement les cartes du joueur
    void updateOpponentHand(int cardCount); // Modifier dynamiquement les cartes de l'adversaire

};


#endif // GAME_H