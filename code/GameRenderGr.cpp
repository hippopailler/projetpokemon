#include "GameRenderGr.h"
#include "CardManagerGr.h"
#include <iostream>
#include "EnergyManagerGr.h"
#include "StatusManagerGr.h"

CardManager::Card Adversaire;
sf::RectangleShape playerBenchZone; // Zone bleue pour le joueur
sf::RectangleShape opponentBenchZone; // Zone rouge pour l'adversaire

sf::Text playerHPText;
sf::Text opponentHPText;
sf::Font font;

std::vector<StatusManager::Status> StatusPlayer;
std::vector<StatusManager::Status> StatusEnnemy;


GameGr::GameGr(std::mutex& mtx)
    : window1(sf::VideoMode(1000, 1000), "Pokemon"),
    window2(sf::VideoMode(1000, 1000), "Pokemon - Player 2"),
    _mtx(mtx) {
    window1.setPosition(sf::Vector2i(500,0));
    // Chargement du fond
    if (!backgroundTexture.loadFromFile("assets/fond.jpg")) {
        std::cerr << "Erreur: Impossible de charger l'image de fond.\n";
        return;
    }
    
    backgroundSprite.setTexture(backgroundTexture);

    // Définir la taille standard des cartes
    CardManager::getInstance().setTargetSize(150.f, 200.f);

    // Initialisation des zones de banc
    playerBenchZone.setSize(sf::Vector2f(175.f, 500.f)); 
    playerBenchZone.setPosition(82.f, 275.f); // Position en bas
    playerBenchZone.setFillColor(sf::Color(0, 0, 255, 100));

    opponentBenchZone.setSize(sf::Vector2f(175.f, 500.f)); 
    opponentBenchZone.setPosition(681.f, 275.f); 
    opponentBenchZone.setFillColor(sf::Color(255, 0, 0, 100)); // Rouge transparent
    
    // Initialisation du contour
    borderRectangle.setPosition(10, 10);
    borderRectangle.setSize(sf::Vector2f(window1.getSize().x - 20, window1.getSize().y - 20));
    borderRectangle.setFillColor(sf::Color::Transparent); // No fill color
    borderRectangle.setOutlineThickness(10); // Border thickness
    borderRectangle.setOutlineColor(sf::Color::White); // Border color

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

    initializeHands(5, 5);
}

void GameGr::initializeHands(int playerCardCount, int opponentCardCount) {
    // Initialisation de la main du joueur
    playerHand.clear();
    /*
    addStatus("poison", 1);
    addStatus("poison", 1);
    addStatus("sleep", 0);
*/
    // Initialisation de la main de l'adversaire
    opponentHand.clear();
}

void GameGr::positionCardsAdv(sf::Sprite& sprite, int index, int yPosition) {
    sprite.setPosition(50 + index *120 , yPosition); // Espacement horizontal
}

void GameGr::positionCards(sf::Sprite& sprite, int index) {
    if (index >= 10){ //carte dans la main
        sprite.setPosition(200 + (index-9) * 120, 800);
    }
    if(index == 1){ //carte active
        sprite.setPosition(400, 575);
    }
    if(2 <= index and index < 5){ //carte banc
        sprite.setPosition(100, 275 + (index-2)*150);
    }
    if(index == 5){ //carte active ennemi
        sprite.setPosition(400, 300);
    }
    if(6 <= index and index < 9){ //carte banc ennemi
        sprite.setPosition(700, 275 + (index-6)*150);
    }
}

void GameGr::addCard(const std::string& cardID, int index) {
    // Vérifier s'il y a déjà une carte à cet index
    for (const auto& card : playerHand) {
        if (card.index == index) {
            removeCard(index);
        }
    }
    CardManager::Card card = CardManager::getInstance().createCard(cardID);
    positionCards(card.sprite, index);
    // Ajoutez la carte à la collection de cartes du jeu
    card.index = index;
    playerHand.push_back(card);
}

void GameGr::removeCard(int index) {
    auto it = std::remove_if(playerHand.begin(), playerHand.end(), [index](const CardManager::Card& card) {
        return card.index == index;
    });
    if (it != playerHand.end()) {
        playerHand.erase(it, playerHand.end());
    }
}

void GameGr::showOpponentHand(int size) {
    // Afficher les cartes de l'adversaire
    int diff = opponentHand.size() - size;
    if (diff > 0) {
        opponentHand.erase(opponentHand.end() - diff, opponentHand.end());
    }
    if (diff < 0) {
        for (int i = opponentHand.size(); i < size; i++) {
            sf::Sprite backSprite = CardManager::getInstance().createBackSprite();
            positionCardsAdv(backSprite, i, 50); // Espacement horizontal (haut de l'écran)
            opponentHand.push_back(backSprite);
        }
    }
}

void GameGr::addOpponentCard(const std::string& name) {
    sf::Sprite cardSprite = CardManager::getInstance().createCard(name).sprite;
    positionCardsAdv(cardSprite, opponentHand.size(), 50); // Espacement horizontal (haut de l'écran)
    opponentHand.push_back(cardSprite);
}

// attention, ici la main est la main du joueur
void GameGr::cleanPlayerHand() {
    for(auto& card : playerHand){
        if(card.index >= 10) removeCard(card.index);
    }
} 

void GameGr::cleanOpponentHand() {
    opponentHand.clear();
}

void GameGr::addEnergy(const typeEnergy energie, int index) {
    EnergyManager:: Energy energy = EnergyManager::getInstance().createEnergy(energie,index);
    positionEnergy(energy.sprite, index,EnergyPlayer);
    //energy.index = index;
    // Ajoutez la carte à la collection de cartes du jeu
    EnergyPlayer.push_back(energy);
}

void GameGr::removeEnergy(energyList energies, int index){
    std::map<typeEnergy, unsigned int> energiesMap = energies.energy();
    for (const auto& energy : energiesMap) {
        int count = energy.second;
        for (auto it = EnergyPlayer.begin(); it != EnergyPlayer.end() && count > 0; ) {
            if (it->index == index && it->type == energy.first) {
                it = EnergyPlayer.erase(it);
                --count;
            } else {
                ++it;
            }
        }
    }
}

void GameGr::removeAllEnergy(int index){
    for (auto energy = EnergyPlayer.begin(); energy != EnergyPlayer.end();){
        if (energy->index == index){
            energy = EnergyPlayer.erase(energy);
        }
        else{
            ++energy;
        }
    }
}

void GameGr::changeBorder(int player) {
    if (player == 0) {
        borderRectangle.setOutlineColor(sf::Color::Blue);
    } else {
        borderRectangle.setOutlineColor(sf::Color::Red);
    }
}

void GameGr::addStatus(const std::string& name, int player) {
    StatusManager::Status status = StatusManager::getInstance().createStatus(name,name,player);
    positionStatus(status.sprite, player);
    // Ajoutez la carte à la collection de cartes du jeu
    if (player == 1){
        StatusPlayer.push_back(status);
    }
    else{
        StatusEnnemy.push_back(status);
    }
}

void GameGr::positionEnergy(sf::Sprite& sprite, int index,std::vector<EnergyManager::Energy> EnergyPlayer) {
    int count = 0;
    for (const auto& energy : EnergyPlayer) {
        if (energy.index == index){
            count++;
        }
    } //compte combien d'énergie sont déjà sur la carte
    
    
    if (index == 1){
        sprite.setPosition(550, 590 + count*40);
    }
    if(index==5){
        sprite.setPosition(360, 310 + count * 40);
    }
    if(2 <= index and index < 5){ //carte banc
        sprite.setPosition(60, 280 + (index-2)*150+count*40);
    }

    if(6 <= index and index < 9){ //carte banc ennemi
        sprite.setPosition(850, 280 + (index-6)*150+count*40);
    }
}

void GameGr::positionStatus(sf::Sprite& sprite, int player) {
    if (player == 1){
        sprite.setPosition(350, 575+40);
    }
    else{
        sprite.setPosition(560, 300 + 40);
    }
}

void GameGr::handleMouseClick(const sf::Event::MouseButtonEvent& mouseEvent) {
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

void GameGr::displayCardInLarge(const sf::Sprite& card) {
    // Récupérer la texture de la carte
    const sf::Texture* cardTexture = card.getTexture();
    if (!cardTexture) {
        std::cerr << "Erreur : Texture de la carte introuvable pour l'agrandissement.\n";
        return;
    }

    // Créer une texture locale pour garantir qu'elle reste valide
    sf::Texture largeCardTexture = *cardTexture;

    sf::RenderWindow largeWindow(sf::VideoMode(300, 400), "Carte en grand");
    largeWindow.setPosition(sf::Vector2i(800,400));
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

void GameGr::switchCard(int index1, int index2) {
    // Échange des indices des cartes
    for (auto& card : playerHand) {
        if (card.index == index1) {
            card.index = index2;
            positionCards(card.sprite, index2);
        } else if (card.index == index2) {
            card.index = index1;
            positionCards(card.sprite, index1);
        }
    }

    // Mettre à jour les indices des énergies associées
    for (auto& energy : EnergyPlayer) {
        if (energy.index == index1) {
            energy.index = index2;
        } else if (energy.index == index2) {
            energy.index = index1;
        }
    }

    //Supprimer les statuts sur les cartes actives si elles sont échangées
    for (auto& status : StatusPlayer) {
        if (status.index == index1 || status.index == index2) {
                        StatusPlayer.erase(StatusPlayer.begin());
                    }
                }

    for (auto& status : StatusEnnemy) {
        if (status.index == index1 || status.index == index2) {
                        StatusEnnemy.erase(StatusEnnemy.begin());
                    }
                }            

    // Repositionner toutes les énergies
    for (auto& energy : EnergyPlayer) {
        int count = 0;
        for (const auto& e : EnergyPlayer) {
            if (e.index == energy.index) {
                ++count;
                if (&e == &energy) break; // Compte les énergies jusqu'à celle-ci
            }
        }

        // Nouvelle position selon l'index et le décalage
        if (energy.index == 1) { // Carte active du joueur
            energy.sprite.setPosition(550, 590 + (count - 1) * 40);
        } else if (energy.index == 5) { // Carte active de l'adversaire
            energy.sprite.setPosition(360, 310 + (count - 1) * 40);
        } else if (2 <= energy.index && energy.index < 5) { // Banc du joueur
            energy.sprite.setPosition(60, 280 + (energy.index - 2) * 150 + (count - 1) * 40);
        } else if (6 <= energy.index && energy.index < 9) { // Banc de l'adversaire
            energy.sprite.setPosition(850, 280 + (energy.index - 6) * 150 + (count - 1) * 40);
        }
    }

    //updateActiveHPTexts();
}

void GameGr::updateActiveHPTexts(int newHP, int player) {
    if (player == 0) {
        playerHPText.setString("HP: " + std::to_string(newHP));
    } else {
        opponentHPText.setString("HP: " + std::to_string(newHP));
    }
}

/*
void GameGr::updateActiveHPTexts() {
    for (const auto& card : playerHand) {
        if (card.index == 1) { // Carte active du joueur
            playerHPText.setString("HP: " + std::to_string(card.hp));
        } else if (card.index == 5) { // Carte active de l'adversaire
            opponentHPText.setString("HP: " + std::to_string(card.hp));
        }
    }
}
*/


void GameGr::attaque(int attackerIndex, int damage) {
    // Parcourir les cartes pour trouver la carte correspondant à l'index
    for (auto& card : playerHand) {
        if (card.index == attackerIndex) {
            // Réduire les points de vie
            //card.hp -= damage;
            //if (card.hp < 0) card.hp = 0; // Évite les HP négatifs

            // Mettre à jour le texte correspondant uniquement pour la carte active ciblée
            if (attackerIndex == 1) { // Carte active du joueur
                playerHPText.setString("HP: " + std::to_string(600000));
            } else if (attackerIndex == 5) { // Carte active de l'adversaire
                opponentHPText.setString("HP: " + std::to_string(10000));
            
            }
            return; // Une fois le texte mis à jour, on sort de la fonction
        }
    }
}


void GameGr::handleKeyPress(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Space:
            switchCard(1, 2); // Exemple : changement de carte
            break;
        case sf::Keyboard::A:
            //addCard("Riolu", 12, 70); // Ajout d'une carte
            break;
        case sf::Keyboard::B:
            attaque(5, 20); // Attaque avec 20 dégâts
            break;
        case sf::Keyboard::S:
            attaque(1, 20); // Une autre attaque
            break;
        case sf::Keyboard::H:
            attaque(1, -10); // Soin (dégâts négatifs)
            break;
        case sf::Keyboard::E:
            addEnergy(WATER, 1); // Ajout d'énergie
            break;
        default:
            std::cout << "Touche non attribuée." << std::endl;
            break;
    }
}


void GameGr::renderWindow() {
    std::lock_guard<std::mutex> lock(_mtx);
    window1.clear();
    window2.clear();
    window1.draw(backgroundSprite); // Dessiner le fond
    window2.draw(backgroundSprite);

    // Dessiner les zones de banc
    window1.draw(playerBenchZone);
    window1.draw(opponentBenchZone);
    window2.draw(playerBenchZone);
    window2.draw(opponentBenchZone);


    for (const auto& card : playerHand) {
        // On dessinne les cartes pour le J1
        window1.draw(card.sprite);
        //sf::Sprite cardSprite2 = card.sprite;
        // Modifier l'image du sprite pour window2  dans la main
        if (card.index > 9) { // carte dans la main
            sf::Sprite cardSprite2 = CardManager::getInstance().createBackSprite();
            cardSprite2.setPosition(card.sprite.getPosition());
            window2.draw(cardSprite2);
        }
        else{
            window2.draw(card.sprite);
        }
    }

    for (const auto& card : opponentHand) {
        window2.draw(card);
        sf::Sprite cardSprite1 = CardManager::getInstance().createBackSprite();
        cardSprite1.setPosition(card.getPosition());
        window1.draw(cardSprite1);
    }

    // Dessiner les points de vie
    window1.draw(playerHPText);
    window1.draw(opponentHPText);
    window2.draw(playerHPText);
    window2.draw(opponentHPText);

    for (const auto& energy : EnergyPlayer) {
        window1.draw(energy.sprite);
        window2.draw(energy.sprite);
    }

    for (const auto& status : StatusPlayer) {
        window1.draw(status.sprite);
        window2.draw(status.sprite);
    }
    for (const auto& status : StatusEnnemy) {
        window1.draw(status.sprite);
        window2.draw(status.sprite);
    }

    window1.draw(borderRectangle);
    window2.draw(borderRectangle);
    window1.display();
    window2.display();
}

void GameGr::run() {
    while (window1.isOpen() || window2.isOpen() ) {
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window1.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                handleMouseClick(event.mouseButton);
            } else if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event.key.code); // Appel d'une fonction dédiée
            }
        }

        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window2.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                handleMouseClick(event.mouseButton);
            } else if (event.type == sf::Event::KeyPressed) {
                handleKeyPress(event.key.code);
            }
        }
        // Dessiner la fenêtre
        renderWindow();
    }
}

