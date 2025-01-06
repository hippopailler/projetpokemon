#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "CardManager.h"
#include "StatusManager.h"
#include "EnergyManager.h"



class Game {
public:
    Game();
    void run();

    void positionEnergy(sf::Sprite &sprite, int index, std::vector<EnergyManager::Energy> EnergyPlayer);

    void positionStatus(sf::Sprite &sprite, int player);

    void handleMouseClick(const sf::Event::MouseButtonEvent &mouseEvent);

    void displayCardInLarge(const sf::Sprite &card);

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Player player1;
    Player player2;

    
    std::vector<CardManager::Card> playerHand;     // Cartes du joueur (dos visible)
    std::vector<sf::Sprite> opponentHand;
    std::vector<EnergyManager::Energy> EnergyPlayer; // énergie du joueur

    CardManager::Card MainCard;
    


    void initializeHands(int playerCardCount, int opponentCardCount); // Initialiser les mains

    void positionCardsAdv(sf::Sprite &sprite, int index, int yPosition);

    void positionCards(sf::Sprite &sprite, int index);

    void addCard(const std::string &name, int x,int hp);

    

    

    void addEnergy(const std::string &name, int index);

    void addStatus(const std::string &name, int player);
};


#endif // GAME_H


