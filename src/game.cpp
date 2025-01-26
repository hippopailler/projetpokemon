#include "game.h"
#include <iostream>

Game::Game(Player* player1, Player* player2, GameGr* gameRender){
    _players[0] = player1;
    _players[1] = player2;
    _activePlayer = 0;
    _turn = 0;
    _energyPlayed = false;
    _winner = -1;
    _energy = COLORLESS;
    _gameRender = gameRender;
}

// Mutateur
void Game::draw(){
    _players[_activePlayer]->draw();
}

void Game::endTurn(){
    _activePlayer = 1 - _activePlayer;
    _turn++;
    _energyPlayed = false;
}

void Game::attack(Move move){
    Pokemon* activePokemon = _players[_activePlayer]->activePokemon();
    Pokemon* opponentPokemon = _players[1 - _activePlayer]->activePokemon();
    bool canUse = (activePokemon->energyAttached()).enoughEnergy(move.cost());
    if (canUse){
        unsigned int dmg = activePokemon->attackWithMove(move);
        opponentPokemon->takeDamage(dmg);
        if (opponentPokemon->isFainted()){
            std::cout << "Le pokemon adverse est KO\n";
            if (!_players[1 - _activePlayer]->hand()->hasPokemonCard()){
                _winner = _activePlayer;
                return;
            }
            _players[1 - _activePlayer]->switchActive();
        }
        endTurn();
        return;
    }
    std::cout<< "Pas assez d'énergie\n";
    chooseAction();
}

void Game::attachEnergyActive(typeEnergy energy){
    if (_energyPlayed){
        std::cout << "Impossible d'attacher plusieurs énergie par tour\n";
        return;
    }
    if (_turn == 0){
        std::cout << "Impossible d'attacher de l'énergie au premier tour\n";
        return;
    }
    _players[_activePlayer]->attachEnergyActive(energy);
    std::cout << "Energie attachée\n";
    _energyPlayed = true;
}

void Game::attachEnergyBench(typeEnergy energy, unsigned int slot){
    _players[_activePlayer]->attachEnergyBench(energy, slot);
}

void Game::retreat(){
    if (_players[_activePlayer]->bench()->isEmpty()){
        std::cout << "Le banc est vide\n";
        return;
    }
    if (!_players[_activePlayer]->activePokemon()->canRetreat()){
        std::cout << "Pas assez d'énergie pour battre en retraite\n";
        return;
    }
    int choice = 0;
    do {
        std::cout << "Choisissez nouveau pokémon actif :";
        std::cin >> choice;
    } while (choice < 0 || choice > 3 || !_players[_activePlayer]->bench()->pokemonInSlot(choice));
    _players[_activePlayer]->activePokemon()->detachEnergy(_players[_activePlayer]->activePokemon()->energyAttached());
    _players[_activePlayer]->switchActive(choice);
}

void Game::chooseAction() {
    //_players[_activePlayer]->showBoard();
    std::cout << "Choisissez une action :\n";
    std::cout << "1. Attacher une énergie\n";
    std::cout << "2. Evoluer\n";
    std::cout << "3. Placer un pokémon sur le banc\n";
    std::cout << "4. Battre en retraite\n";
    std::cout << "5. Attaquer\n";
    std::cout << "6. Finir le tour\n";
    int choice = 0;
    do {
        std::cout << "Choisissez votre action :";
        std::cin >> choice;
    } while (choice < 1 || choice > 6);
    switch (choice){
    case 1:{
        attachEnergyActive(_energy);
        chooseAction();
        break;
    }
    case 2:{
        evolve();
        chooseAction();
        break;
    }
    case 3:{
        placePokemonOnBench();
        chooseAction();
        break;
    }
    case 4:{
        retreat();
        chooseAction();
        break;
    }
    case 5:{
        if (_turn == 0){
            std::cout << "Impossible d'attaquer au premier tour\n";
            chooseAction();
            break;
        }
        Pokemon* activePokemon = _players[_activePlayer]->activePokemon();
        Move move = activePokemon->chooseMove();
        attack(move);
        break;
    }
    case 6:{
        endTurn();
        break;
    }
    default:
        break;
    }
}

void Game::beginTurn(){
    std::cout << "Début du tour " << _turn+1 << " : c'est au joueur " << _activePlayer + 1
    << "de jouer"<< std::endl;
    draw();
    _energy = _players[_activePlayer]->randomEnergy();
    std::cout << "Energie du tour : " << typeEnergyToString(_energy) << "\n";
    _players[_activePlayer]->printHand();
    chooseAction();
}

void Game::placeActivePokemon(int player){
    int choice = 0;
    do {
        std::cout << "Choisissez votre pokemon actif :";
        std::cin >> choice;
    } while ( (choice < 0 || choice > 5) || !_players[player]->hand()->cards()[choice]->isPokemon() || !dynamic_cast<Pokemon*>(_players[player]->hand()->cards()[choice].get())->isBasic());
    //const std::unique_ptr<Card>& chosenCard = _players[player]->hand()->cards()[choice];
    //Pokemon* chosenPokemon = dynamic_cast<Pokemon*>(chosenCard.get());
    _players[player]->placeActivePokemon(choice, _turn);
    _players[player]->hand()->removeCard(choice);
    int position = player == 0 ? 1 : 5;
    addCard(_players[player]->activePokemon()->cardID(), position);
    updateActiveHPTexts(player);
}

void Game::placePokemonOnBench(){
    if (_players[_activePlayer]->bench()->isFull()){
        std::cout << "Le banc est plein\n";
        return;
    }
    if (!_players[_activePlayer]->hand()->hasBasicPokemonCard()){
        std::cout << "Pas de pokémon de base en main\n";
        return;
    }
    _players[_activePlayer]->printHand();
    int choice = 0;
    do {
        std::cout << "Choisissez le pokémon à placer sur le banc :";
        std::cin >> choice;
    } while ( (choice < 0 || choice > 5) || !_players[_activePlayer]->hand()->cards()[choice]->isPokemon());
    _players[_activePlayer]->placePokemonOnBench(choice, _turn);
    _players[_activePlayer]->hand()->removeCard(choice);
}

void Game::beginGame(){
    for (int i = 0; i < 2; i++){
        _players[i]->shuffleDeck();
        _players[i]->draw(5);
        while (!_players[i]->hand()->hasBasicPokemonCard()){
            _players[i]->mulligan();
        }
        std::cout << "Joueur " << i+1 << ", choisissez un pokémon actif : \n";
        _players[i]->printHand();
        placeActivePokemon(i);
    }
    while (_winner == -1){
        beginTurn();
    }
}

void Game::evolve(){
    // choix du pokemon à évoluer
    unsigned int choice;
    std::cout << "Choississez le pokémon à évoluer\n";
    _players[_activePlayer]->showBoard();
    do{
        std::cin >> choice;
    } while (choice > 5);

    Pokemon* toEvolve;
    if (choice == 0){
        toEvolve = _players[_activePlayer]->activePokemon();
    } else {
        if (_players[_activePlayer]->bench()->pokemonInSlot(choice-1)){
            toEvolve = _players[_activePlayer]->bench()->getCard(choice-1);
        } else {
            std::cout << "Il n'y a pas de pokémon à cet emplacement\n";
            return;
        }
    }

    // choix de la carte d'évolution
    std::cout << "Choisissez l'évolution\n";
    _players[_activePlayer]->printHand();
    do{
        std::cin >> choice;
    } while (choice >= _players[_activePlayer]->hand()->size());

    std::unique_ptr<Card> card = _players[_activePlayer]->hand()->takeCard(choice);
    Pokemon* evolution = dynamic_cast<Pokemon*>(card.get());

    // evolution
    if (evolution->evolveFrom().has_value() && toEvolve->canEvolve(_turn, evolution->evolveFrom().value())){
        toEvolve->evolve(evolution, _turn);
        std::cout << "Le pokémon a évolué\n";
        card.release();
    } else {
        std::cout << "Pas d'évolution" << std::endl;
        _players[_activePlayer]->hand()->addCard(std::move(card));
    }
}

// Graphismes

void Game::updateActiveHPTexts(int player){
    _gameRender->updateActiveHPTexts(_players[player]->activePokemon()->hp(), player);
}

void Game::addCard(const std::string& cardID, int index){
    _gameRender->addCard(cardID, index);
}

// Accesseurs

unsigned int Game::turn() const{
    return _turn;
}

const Player* Game::current_player() const{
    return _players[_activePlayer];
}