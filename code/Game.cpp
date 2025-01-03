#include "Game.h"
#include "CardManager.h"
#include <iostream>

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
    
    // Ajout de cartes
    addCard("Riolu", 100, 800);
    addCard("Pachirisu", 220, 800);
    addCard("Etourmi", 340, 800);
    addCard("Mascaiman", 460, 800);

    addCard("Tarsal", 580, 800);
    initializeHands(5, 5);

}

void Game::initializeHands(int playerCardCount, int opponentCardCount) {
    // Initialisation de la main du joueur
    playerHand.clear();
    for (int i = 0; i < playerCardCount; ++i) {
        sf::Sprite backSprite = CardManager::getInstance().createBackSprite();
        backSprite.setPosition(50 + i * (150 + 20), 800); // Espacement horizontal
        playerHand.push_back(backSprite);
    }

    // Initialisation de la main de l'adversaire
    opponentHand.clear();
    for (int i = 0; i < opponentCardCount; ++i) {
        sf::Sprite backSprite = CardManager::getInstance().createBackSprite();
        backSprite.setPosition(100 + i * 110, 100); // Espacement horizontal (haut de l'écran)
        opponentHand.push_back(backSprite);
    }
}

void Game::updatePlayerHand(int cardCount) {
    playerHand.clear();
    for (int i = 0; i < cardCount; ++i) {
        sf::Sprite backSprite = CardManager::getInstance().createBackSprite();
        backSprite.setPosition(50 + i * (150 + 20), 800);
        playerHand.push_back(backSprite);
    }
}

void Game::updateOpponentHand(int cardCount) {
    opponentHand.clear();
    for (int i = 0; i < cardCount; ++i) {
        sf::Sprite backSprite = CardManager::getInstance().createBackSprite();
        backSprite.setPosition(50 + i * (150 + 20), 100);
        opponentHand.push_back(backSprite);
    }
}



void Game::addCard(const std::string& cardName, float x, float y) {
    sf::Sprite cardSprite = CardManager::getInstance().createCardSprite(cardName);
    cardSprite.setPosition(x, y);
    cardSprites.push_back(cardSprite);
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
        for (const auto& card : cardSprites) {
            window.draw(card); // Dessiner chaque carte
        }
        // Dessiner la main de l'adversaire
        for (const auto& card : opponentHand) {
            window.draw(card);
        }
        window.display();
    }
}