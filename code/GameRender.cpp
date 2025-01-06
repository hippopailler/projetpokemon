#include "GameRender.h"
#include "CardManager.h"
#include <iostream>
#include "EnergyManager.h"
#include "StatusManager.h"

CardManager::Card Adversaire;
sf::RectangleShape playerBenchZone; // Zone bleue pour le joueur
sf::RectangleShape opponentBenchZone; // Zone rouge pour l'adversaire

sf::Text playerHPText;
sf::Text opponentHPText;
sf::Font font;

std::vector<StatusManager::Status> StatusPlayer;
std::vector<StatusManager::Status> StatusEnnemy;


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

    // Initialisation des zones de banc
    playerBenchZone.setSize(sf::Vector2f(150.f, 500.f)); 
    playerBenchZone.setPosition(100.f, 275.f); // Position en bas
    playerBenchZone.setFillColor(sf::Color(0, 0, 255, 100));

    opponentBenchZone.setSize(sf::Vector2f(150.f, 500.f)); 
    opponentBenchZone.setPosition(675.f, 275.f); 
    opponentBenchZone.setFillColor(sf::Color(255, 0, 0, 100)); // Rouge transparent
    
    initializeHands(5, 5);
    ActiveCardPlayer("Bulbasaur",70);
    Adversaire = ActiveCardEnnemy("Tarsal",70);

if (!font.loadFromFile("assets/Bubble Garden Regular.ttf")) {
        std::cerr << "Erreur: Impossible de charger la police.\n";
        return;
    }
    playerHPText.setFont(font);
    playerHPText.setCharacterSize(30);
    playerHPText.setFillColor(sf::Color::Black);
    playerHPText.setPosition(320, 575);

    opponentHPText.setFont(font);
    opponentHPText.setCharacterSize(30);
    opponentHPText.setFillColor(sf::Color::Black);
    opponentHPText.setPosition(560, 300);
}

void Game::initializeHands(int playerCardCount, int opponentCardCount) {
    // Initialisation de la main du joueur
    playerHand.clear();
    addCard("Riolu", 1, 800,60);
    addCard("Pachirisu", 2, 800,60);
    addCard("Etourmi", 3, 800,60);
    addCard("Mascaiman", 4, 800,60);
    addCard("Tarsal", 5, 800,60);

    addEnergy("grass", 1, 1);
    addEnergy("grass", 2, 1);
    addEnergy("psy", 1, 0);
    addEnergy("psy", 2, 0);

    addStatus("poison", 1);
    addStatus("poison", 1);
    addStatus("sleep", 0);

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

void Game::addCard(const std::string& name, int index, int y,int hp) {
    CardManager::Card  card = CardManager::getInstance().createCard(name,hp);
    positionCards(card.sprite, index, y);
    // Ajoutez la carte à la collection de cartes du jeu
    playerHand.push_back(card);
}

void Game::ActiveCardPlayer(const std::string& name,int hp){
    CardManager::Card activeCard = CardManager::getInstance().createCard(name,hp);
    MainCard = activeCard;
    MainCard.sprite.setPosition(400,575);
}

CardManager::Card Game::ActiveCardEnnemy(const std::string& name,int hp){
    CardManager::Card activeCard = CardManager::getInstance().createCard(name, hp);
    activeCard.sprite.setPosition(400, 300);
    return activeCard;
}

void Game::addEnergy(const std::string& name, int index, int player) {
    sf::Sprite EnergySprite = EnergyManager::getInstance().createEnergySprite(name);
    positionEnergy(EnergySprite, index, player);
    // Ajoutez la carte à la collection de cartes du jeu
    EnergyPlayer.push_back(EnergySprite);
}

void Game::addStatus(const std::string& name, int player) {
    StatusManager::Status status = StatusManager::getInstance().createStatus(name,name);
    positionStatus(status.sprite, player);
    // Ajoutez la carte à la collection de cartes du jeu
    if (player == 1){
        StatusPlayer.push_back(status);
    }
    else{
        StatusEnnemy.push_back(status);
    }
}

void Game::positionEnergy(sf::Sprite& sprite, int index, int player) {
    if (player == 1){
        sprite.setPosition(550, 775 - index*40);
    }
    else{
        sprite.setPosition(360, 270 + index * 40);
    }
}

void Game::positionStatus(sf::Sprite& sprite, int player) {
    if (player == 1){
        sprite.setPosition(350, 575+40);
    }
    else{
        sprite.setPosition(560, 300 + 40);
    }
}

void Game::handleMouseClick(const sf::Event::MouseButtonEvent& mouseEvent) {
    if (mouseEvent.button == sf::Mouse::Left) {
        for (const auto& card : playerHand) {
            if (card.sprite.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
                displayCardInLarge(card.sprite);
                break;
            }
        }
        
        if (MainCard.sprite.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
            displayCardInLarge(MainCard.sprite);
            return;
        }

        // Vérifier si la souris est sur la carte active de l'adversaire
        if (Adversaire.sprite.getGlobalBounds().contains(mouseEvent.x, mouseEvent.y)) {
            displayCardInLarge(Adversaire.sprite);
            return;
        }
    }
}

void Game::displayCardInLarge(const sf::Sprite& card) {
    // Récupérer la texture de la carte
    const sf::Texture* cardTexture = card.getTexture();
    if (!cardTexture) {
        std::cerr << "Erreur : Texture de la carte introuvable pour l'agrandissement.\n";
        return;
    }

    // Créer une texture locale pour garantir qu'elle reste valide
    sf::Texture largeCardTexture = *cardTexture;

    sf::RenderWindow largeWindow(sf::VideoMode(300, 400), "Carte en grand");
    sf::Sprite largeCard;
    largeCard.setTexture(largeCardTexture);

    // Ajuster l'échelle pour agrandir la carte
    largeCard.setScale(
        largeWindow.getSize().x / static_cast<float>(largeCardTexture.getSize().x),
        largeWindow.getSize().y / static_cast<float>(largeCardTexture.getSize().y)
    );

    while (largeWindow.isOpen()) {
        sf::Event event;
        while (largeWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                largeWindow.close();
            }
        }

        largeWindow.clear();
        largeWindow.draw(largeCard);
        largeWindow.display();
    }
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                handleMouseClick(event.mouseButton);
            }
        }

        playerHPText.setString("HP: " + std::to_string(MainCard.hp));
        opponentHPText.setString("HP: " + std::to_string(Adversaire.hp));

        window.clear();
        window.draw(backgroundSprite); // Dessiner le fond
        for (const auto& card : playerHand) {
            window.draw(card.sprite); // Dessiner chaque carte
        }

        // Dessiner les zones de banc
        window.draw(playerBenchZone);
        window.draw(opponentBenchZone);

        // Dessiner la main de l'adversaire
        for (const auto& card : opponentHand) {
            window.draw(card);
        }
        window.draw(MainCard.sprite);
        window.draw(Adversaire.sprite);

        // Dessiner les points de vie
        window.draw(playerHPText);
        window.draw(opponentHPText);

        for (const auto& energy : EnergyPlayer) {
            window.draw(energy);
        }


        for (const auto& status : StatusPlayer) {
            window.draw(status.sprite);
        }
        for(const auto& status : StatusEnnemy){
            window.draw(status.sprite);
        }
        window.display();
    }
}


