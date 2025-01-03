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

    
    std::vector<sf::Sprite> playerHand;     // Cartes du joueur (dos visible)
    std::vector<sf::Sprite> opponentHand;

    sf::Sprite MainCard;
    


    void initializeHands(int playerCardCount, int opponentCardCount); // Initialiser les mains
   

    void positionCardsAdv(sf::Sprite &sprite, int index, int yPosition);

    void positionCards(sf::Sprite &sprite, int index, int yPosition);

    void addCard(const std::string &name, int x, int y);

    void ActiveCardPlayer(const std::string &name);

    sf::Sprite ActiveCardEnnemy(const std::string &name);
};


#endif // GAME_H