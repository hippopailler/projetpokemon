#include "game.h"
#include <iostream>

Game::Game(Player* player1, Player* player2) {
    _players[0] = player1;
    _players[1] = player2;
    _activePlayer = 0;
    _turn = 0;
    _energyPlayed = false;
    _winner = -1;
    _energy = COLORLESS;
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
            std::cout << CYAN << "Le pokemon adverse est KO\n" << RESET;
            if (_players[1 - _activePlayer]->bench()->isEmpty()){
                _winner = _activePlayer;
                return;
            }
            unsigned int point = opponentPokemon->isEx() ? 2:1;
            _players[_activePlayer]->gainPoints(point);
            if (_players[_activePlayer]->hasWon()){
                _winner = _activePlayer;
                return;
            }
            _players[1 - _activePlayer]->switchActive();
            _players[1 - _activePlayer]->activePokemon()->onPlayed(_turn);
        }
        endTurn();
        return;
    }
    std::cout<< RED << "Pas assez d'énergie\n" << RESET;
    chooseAction();
}

void Game::attachEnergyActive(typeEnergy energy){
    if (_energyPlayed){
        std::cout << RED << "Impossible d'attacher plusieurs énergie par tour\n" << RESET;
        return;
    }
    if (_turn == 0){
        std::cout << RED <<"Impossible d'attacher de l'énergie au premier tour\n" << RESET;
        return;
    }
    _players[_activePlayer]->attachEnergyActive(energy);
    std::cout << GREEN << "Energie attachée\n" << RESET;
    _energyPlayed = true;
}

void Game::attachEnergyBench(typeEnergy energy, unsigned int slot){
    _players[_activePlayer]->attachEnergyBench(energy, slot);
}

void Game::retreat(){
    if (_players[_activePlayer]->bench()->isEmpty()){
        std::cout << RED << "Le banc est vide\n" << RESET;
        return;
    }
    if (!_players[_activePlayer]->activePokemon()->canRetreat()){
        std::cout << RED << "Pas assez d'énergie pour battre en retraite\n" << RESET;
        return;
    }
    int choice = 0;
    do {
        std::cout << BLUE << "Choisissez nouveau pokémon actif :" << RESET;
        std::cin >> choice;
    } while (choice < 0 || choice > 3 || !_players[_activePlayer]->bench()->pokemonInSlot(choice));
    _players[_activePlayer]->activePokemon()->detachEnergy(_players[_activePlayer]->activePokemon()->energyAttached());
    _players[_activePlayer]->switchActive(choice);
}

void Game::chooseAction() {
    //_players[_activePlayer]->showBoard();
    std::cout << MAGENTA << BOLD
    << "Actions :\n" << RESET << MAGENTA
    << "1. Attacher une énergie\n"
    << "2. Evoluer\n"
    << "3. Placer un pokémon sur le banc\n"
    << "4. Battre en retraite\n"
    << "5. Attaquer\n"
    << "6. Finir le tour\n"
    << RESET;
    int choice = 0;
    do {
        std::cout << BLUE << "Choisissez votre action :" << RESET;
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
            std::cout << RED << "Impossible d'attaquer au premier tour\n" << RESET;
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
    << " de jouer"<< std::endl;
    draw();
    _energy = _players[_activePlayer]->randomEnergy();
    std::cout << "Energie du tour : " << BOLD << MAGENTA << typeEnergyToString(_energy) << RESET <<"\n";
    _players[_activePlayer]->printHand();
    chooseAction();
}

void Game::placeActivePokemon(int player){
    int choice = 0;
    do {
        std::cout << BLUE << "Choisissez votre pokemon actif :" << RESET;
        std::cin >> choice;
    } while ( (choice < 0 || choice > 5) || !_players[player]->hand()->cards()[choice]->isPokemon() || !dynamic_cast<Pokemon*>(_players[player]->hand()->cards()[choice].get())->isBasic());
    //const std::unique_ptr<Card>& chosenCard = _players[player]->hand()->cards()[choice];
    //Pokemon* chosenPokemon = dynamic_cast<Pokemon*>(chosenCard.get());
    _players[player]->placeActivePokemon(choice, _turn);
    _players[player]->hand()->removeCard(choice);
}

void Game::placePokemonOnBench(){
    if (_players[_activePlayer]->bench()->isFull()){
        std::cout << RED << "Le banc est plein\n" << RESET;
        return;
    }
    if (!_players[_activePlayer]->hand()->hasBasicPokemonCard()){
        std::cout << RED << "Pas de pokémon de base en main\n" << RESET;
        return;
    }
    _players[_activePlayer]->printHand();
    int choice = 0;
    do {
        std::cout << BLUE << "Choisissez le pokémon à placer sur le banc :" << RESET;
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
    std::cout << "\nLe gagnant est le joueur " << _winner << std::endl;
}

void Game::evolve(){
    // choix du pokemon à évoluer
    unsigned int choice;
    if (!_players[_activePlayer]->hand()->hasPokemonCard()){
        std::cout << RED << "Pas de pokémon dans la main";
        return;
    }

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
            std::cout << RED << "Il n'y a pas de pokémon à cet emplacement\n" << RESET;
            return;
        }
    }
    // choix de la carte d'évolution
    std::cout << BLUE << "Choisissez l'évolution\n" << RESET;
    _players[_activePlayer]->printHand();
    do{
        std::cin >> choice;
    } while (choice >= _players[_activePlayer]->hand()->size());

    std::unique_ptr<Card> card = _players[_activePlayer]->hand()->takeCard(choice);
    Pokemon* evolution = dynamic_cast<Pokemon*>(card.get());

    // evolution
    if (evolution->evolveFrom().has_value() && toEvolve->canEvolve(_turn, evolution->evolveFrom().value())){
        toEvolve->evolve(evolution, _turn);
        std::cout << GREEN << "Le pokémon a évolué" << RESET << std::endl;
        card.release();
    } else {
        std::cout << RED << "Pas d'évolution" << RESET << std::endl;
        _players[_activePlayer]->hand()->addCard(std::move(card));
    }
}

// Accesseurs

unsigned int Game::turn() const{
    return _turn;
}

const Player* Game::current_player() const{
    return _players[_activePlayer];
}