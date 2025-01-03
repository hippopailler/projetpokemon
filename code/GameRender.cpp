#include "GameRender.h"
#include "CardManager.h"
#include <iostream>
#include "EnergyManager.h"

sf::Sprite Adversaire;


Game::Game()
    : window(sf::VideoMode(1000, 1000), "Pokemon") {
    // Chargement du fond
    if (!backgroundTexture.loadFromFile("assets/fond.jpg")) {
        std::cerr << "Erreur: Impossible de charger l'image de fond.\n";
        return;
    }
    backgroundSprite.setTexture(backgroundTexture);
    // Définir la taille standard des cartes
    CardManager::getInstance().setTargetSize(150.f, 200.f);
    
    initializeHands(5, 5);
    ActiveCardPlayer("Bulbasaur");
    Adversaire = ActiveCardEnnemy("Tarsal");

}


void Game::initializeHands(int playerCardCount, int opponentCardCount) {
    // Initialisation de la main du joueur
    playerHand.clear();
    addCard("Riolu", 1, 800);
    addCard("Pachirisu", 2, 800);
    addCard("Etourmi", 3, 800);
    addCard("Mascaiman", 4, 800);
    addCard("Tarsal", 5, 800);

    addEnergy("water", 1, 1);
    addEnergy("fire", 2, 1);
    addEnergy("grass", 1, 0);
    addEnergy("electric", 2, 0);

    // Initialisation de la main de l'adversaire
    opponentHand.clear();
    for (int i = 0; i < opponentCardCount; ++i) {
        sf::Sprite backSprite = CardManager::getInstance().createBackSprite();
        positionCardsAdv(backSprite, i, 50); // Espacement horizontal (haut de l'écran)
        opponentHand.push_back(backSprite);
    }
}


void Game::positionCardsAdv(sf::Sprite& sprite, int index, int yPosition) {
    sprite.setPosition(50 + index *120 , yPosition); // Espacement horizontal
}

void Game::positionCards(sf::Sprite& sprite, int index, int yPosition) {
    sprite.setPosition(200 + index * 120, yPosition); 
}

void Game::addCard(const std::string& name, int index, int y) {
    sf::Sprite cardSprite = CardManager::getInstance().createCardSprite(name);
    positionCards(cardSprite, index, y);
    // Ajoutez la carte à la collection de cartes du jeu
    playerHand.push_back(cardSprite);
}

void Game::ActiveCardPlayer(const std::string& name){
    sf::Sprite ActiveCardP = CardManager::getInstance().createCardSprite(name);
    MainCard = ActiveCardP;
    MainCard.setPosition(400,575);
}


sf::Sprite Game::ActiveCardEnnemy(const std::string& name){
    sf::Sprite ActiveCardE = CardManager::getInstance().createCardSprite(name);
    ActiveCardE.setPosition(400,300);
    return ActiveCardE;
}

void Game::addEnergy(const std::string& name, int index, int player) {
    sf::Sprite EnergySprite = EnergyManager::getInstance().createEnergySprite(name);
    positionEnergy(EnergySprite, index, player);
    // Ajoutez la carte à la collection de cartes du jeu
    EnergyPlayer.push_back(EnergySprite);
}

void Game::positionEnergy(sf::Sprite& sprite, int index, int player) {
    if (player == 1){
        sprite.setPosition(550, 775 - index*40);
    }
    else{
        sprite.setPosition(360, 270 + index * 40);
    }
}





void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        

        window.clear();
        window.draw(backgroundSprite); // Dessiner le fond
        for (const auto& card : playerHand) {
            window.draw(card); // Dessiner chaque carte
        }
        // Dessiner la main de l'adversaire
        for (const auto& card : opponentHand) {
            window.draw(card);
        }
        window.draw(MainCard);
        window.draw(Adversaire);


        for (const auto& energy : EnergyPlayer) {
            window.draw(energy);
        }

        window.display();
    }
}


