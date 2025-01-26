#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "CardManagerGr.h"
#include "StatusManagerGr.h"
#include "EnergyManagerGr.h"



class GameGr {
public:
    GameGr();
    void run();

    void renderWindow();

    void handleKeyPress(sf::Keyboard::Key key);

    void positionEnergy(sf::Sprite &sprite, int index, std::vector<EnergyManager::Energy> EnergyPlayer);

    void positionStatus(sf::Sprite &sprite, int player);

    void handleMouseClick(const sf::Event::MouseButtonEvent &mouseEvent);

    void displayCardInLarge(const sf::Sprite &card);

    void PositionEnergySwitch(EnergyManager::Energy &energy,std::vector<EnergyManager::Energy> EnergyPlayer);

    void switchCard(int index1, int index2);

    void updateActiveHPTexts(int newHP, int player);

    void attaque(int attackerIndex, int damage);
    void addCard(const std::string &cardID, int index);
    void removeCard(int index);
    void showOpponentHand(int size);
    void cleanPlayerHand(); 

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    std::vector<CardManager::Card> playerHand;     // Cartes du joueur (dos visible)
    std::vector<sf::Sprite> opponentHand;
    std::vector<EnergyManager::Energy> EnergyPlayer; // énergie du joueur

    CardManager::Card MainCard;
    


    void initializeHands(int playerCardCount, int opponentCardCount); // Initialiser les mains

    void positionCardsAdv(sf::Sprite &sprite, int index, int yPosition);

    void positionCards(sf::Sprite &sprite, int index);

    void addCard(const std::string &name, int x,int hp);

    

    

    void addEnergy(const std::string &name, int index);

    void addStatus(const std::string &name, int player); //player prendra la valeur 1 pour le joueur et 5 pour l'adversaire
};


#endif // GAME_H


